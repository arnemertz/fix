#include "app.hpp"

#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include <ostream>

#include "application_service.hpp"

using namespace fix::cli;
using namespace std::string_view_literals;

namespace {
constexpr auto DESCRIPTION = R"(fix - Issue tracker)"sv;
} // namespace

app::app(std::ostream& out) : out{out} {}

auto app::run(int argc, const char* const* argv) -> int {
  CLI::App cli_app{std::string(DESCRIPTION), "fix"};
  cli_app.require_subcommand(0, 1);
  cli_app.fallthrough();

  // List command
  auto* list_cmd = cli_app.add_subcommand("list", "List all existing issues");
  list_cmd->callback([this]() { 
    list();
  });

  // Create command
  auto* create_cmd = cli_app.add_subcommand("create", "Create a new issue");
  std::string title;
  std::string description;
  create_cmd->add_option("-t,--title", title, "Title of the new issue")->required();
  create_cmd->add_option("-d,--descr", description, "Description text")->required();
  create_cmd->callback([this, &title, &description]() {
    create(title, description);
  });

  // Parse arguments using argc/argv
  try {
    cli_app.parse(argc, argv);
  } catch (const CLI::CallForHelp&) {
    out << cli_app.help();
    return EXIT_SUCCESS;
  } catch (const CLI::ExtrasError&) {
    // Unknown arguments/subcommands
    out << "fix: unknown subcommand. See 'fix --help'.\n";
    return EXIT_FAILURE;
  } catch (const CLI::ParseError& e) {
    // Other parse errors
    out << e.what() << "\n";
    out << "Run with --help for more information.\n";
    return EXIT_FAILURE;
  }

  if (cli_app.get_subcommands().empty()) {
    out << cli_app.help();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int app::list() {
  domain::application_service application_service;
  auto const count = application_service.list();
  out << fmt::format("total: {} issues\n", count);
  return EXIT_SUCCESS;
}

int app::create(std::string const& title, std::string const& description) {
  domain::application_service application_service;
  const auto issue_id = application_service.create(title, description);
  out << fmt::format("Issue created: {}\n", issue_id);
  return EXIT_SUCCESS;
}
