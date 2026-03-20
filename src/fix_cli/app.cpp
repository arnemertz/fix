#include "app.hpp"

#include <CLI/CLI.hpp>
#include <format>
#include <ostream>
#include <string>

#include "description.hpp"
#include "issue_id.hpp"
#include "issue_service.hpp"
#include "title.hpp"

using namespace fix::cli;
using namespace std::string_view_literals;

namespace {

constexpr auto DESCRIPTION = R"(fix - Issue tracker)"sv;

struct app_environment {
  std::ostream& out;
  CLI::App& cli;
  int& exit_code;
};

struct list_command {
  app_environment environment;
  fix::domain::issue_service& service;

  list_command(app_environment environment, fix::domain::issue_service& service)
      : environment{environment}, service{service} {
    environment.cli.add_subcommand("list", "List all existing issues")->callback([this] {
      this->environment.exit_code = execute();
    });
  }

private:
  int execute() const {
    auto const result = service.list();
    if (!result) {
      environment.out << std::format("Error: {}\n", result.error().message());
      return EXIT_FAILURE;
    }
    for (auto const& iss : *result) {
      environment.out << std::format("{} | {} | open\n", iss.id().to_string(), iss.get_title().to_string());
    }
    environment.out << std::format("total: {} issues\n", result->size());
    return EXIT_SUCCESS;
  }
};

struct create_command {
  app_environment environment;
  fix::domain::issue_service& service;
  std::string title;
  std::string description;

  create_command(app_environment environment, fix::domain::issue_service& service)
      : environment{environment}, service{service} {
    auto* const cmd = environment.cli.add_subcommand("create", "Create a new issue");
    cmd->add_option("-t,--title", title, "Title of the new issue");
    cmd->add_option("-d,--descr", description, "Description text");
    cmd->callback([this] { this->environment.exit_code = execute(); });
  }

private:
  int execute() const {
    auto const title_result = fix::domain::title::create(title);
    auto const desc_result = fix::domain::description::create(description);

    bool any_error = false;
    if (!title_result) {
      environment.out << std::format("Error: {}\n", title_result.error().message());
      any_error = true;
    }
    if (!desc_result) {
      environment.out << std::format("Error: {}\n", desc_result.error().message());
      any_error = true;
    }
    if (any_error) {
      return EXIT_FAILURE;
    }

    auto const result = service.create(title, description);
    if (!result) {
      auto const id = fix::domain::issue_id::generate(*title_result, *desc_result);
      environment.out << std::format("Issue already exists: {}\n", id.to_string());
      return EXIT_FAILURE;
    }

    environment.out << std::format("Issue created: {}\n", *result);
    return EXIT_SUCCESS;
  }
};

} // namespace

app::app(std::ostream& out, domain::issue_service& service) : out{out}, service_{service} {}

auto app::run(int argc, char const* const* argv) -> int {
  CLI::App cli_app{std::string(DESCRIPTION), "fix"};
  cli_app.require_subcommand(0, 1);
  cli_app.fallthrough();
  int exit_code = EXIT_SUCCESS;

  app_environment const environment{out, cli_app, exit_code};
  list_command list{environment, service_};
  create_command create{environment, service_};

  try {
    cli_app.parse(argc, argv);
  } catch (CLI::CallForHelp const&) {
    out << cli_app.help();
    return EXIT_SUCCESS;
  } catch (CLI::ExtrasError const&) {
    out << "fix: unknown subcommand. See 'fix --help'.\n";
    return EXIT_FAILURE;
  } catch (CLI::ParseError const& e) {
    out << e.what() << "\n";
    out << "Run with --help for more information.\n";
    return EXIT_FAILURE;
  }

  if (cli_app.get_subcommands().empty()) {
    out << cli_app.help();
    return EXIT_FAILURE;
  }

  return exit_code;
}
