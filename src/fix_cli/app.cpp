#include "app.hpp"

#include <CLI/CLI.hpp>
#include <format>
#include <ostream>

#include "description.hpp"
#include "issue_id.hpp"
#include "issue_service.hpp"
#include "title.hpp"

using namespace fix::cli;
using namespace std::string_view_literals;

namespace {
constexpr auto DESCRIPTION = R"(fix - Issue tracker)"sv;
} // namespace

app::app(std::ostream& out, domain::issue_service& service) : out{out}, service_{service} {}

auto app::run(int argc, const char* const* argv) -> int {
  CLI::App cli_app{std::string(DESCRIPTION), "fix"};
  cli_app.require_subcommand(0, 1);
  cli_app.fallthrough();

  int subcommand_exit_code = EXIT_SUCCESS;

  // List command
  auto* list_cmd = cli_app.add_subcommand("list", "List all existing issues");
  list_cmd->callback([this, &subcommand_exit_code]() {
    subcommand_exit_code = list();
  });

  // Create command
  auto* create_cmd = cli_app.add_subcommand("create", "Create a new issue");
  std::string title;
  std::string description;
  create_cmd->add_option("-t,--title", title, "Title of the new issue");
  create_cmd->add_option("-d,--descr", description, "Description text");
  create_cmd->callback([this, &title, &description, &subcommand_exit_code]() {
    subcommand_exit_code = create(title, description);
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

  return subcommand_exit_code;
}

int app::list() {
  auto const result = service_.list();
  if (!result) {
    out << std::format("Error: {}\n", result.error().message());
    return EXIT_FAILURE;
  }

  for (auto const& iss : *result) {
    out << std::format("{} | {} | open\n", iss.id().to_string(), iss.get_title().to_string());
  }

  out << std::format("total: {} issues\n", result->size());
  return EXIT_SUCCESS;
}

int app::create(std::string const& title, std::string const& description) {
  // Pre-validate both fields to collect all errors
  auto const title_result = domain::title::create(title);
  auto const desc_result = domain::description::create(description);

  bool any_error = false;
  if (!title_result) {
    out << std::format("Error: {}\n", title_result.error().message());
    any_error = true;
  }
  if (!desc_result) {
    out << std::format("Error: {}\n", desc_result.error().message());
    any_error = true;
  }
  if (any_error) {
    return EXIT_FAILURE;
  }

  auto const result = service_.create(title, description);
  if (!result) {
    // Must be a duplicate (validation already passed above)
    // Re-generate the ID so we can show it in the error message
    auto id = domain::issue_id::generate(*title_result, *desc_result);
    out << std::format("Issue already exists: {}\n", id.to_string());
    return EXIT_FAILURE;
  }

  out << std::format("Issue created: {}\n", *result);
  return EXIT_SUCCESS;
}
