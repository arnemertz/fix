#include "app.hpp"

#include <docopt/docopt.h>
#include <fmt/core.h>
#include <ostream>

#include "application_service.hpp"

using namespace fix::cli;
using namespace std::string_view_literals;

namespace {
constexpr auto USAGE = R"(usage: fix [--help] <command> [<args>...]

Options:
  -h --help      This help page

Available commands:
   create        Create a new issue
   setstatus     Set the status of an issue
   list          List all existing issues
   show          Show a specific issue
)"sv;

constexpr auto CREATE_USAGE = R"(usage: fix create -t <title> -d <descr>

Options:
  -t <title> --title=<title> Title of the new issue
  -d <descr> --descr=<descr> Description text
)";
} // namespace

app::app(std::ostream& out) : out{out} {}

auto app::run(const std::vector<std::string_view>& args) -> int {
  std::vector<std::string> const argv(args.begin(), args.end());

  try {
    auto const& parsed_args = docopt::docopt_parse(std::string(USAGE), argv, true, false, true);
    auto const& command = parsed_args.at("<command>").asString();
    return run_command(command, argv);

  } catch (docopt::DocoptExitHelp const&) {
    out << USAGE;
    return EXIT_SUCCESS;

  } catch (docopt::DocoptArgumentError& argError) {
    out << USAGE;
    return EXIT_FAILURE;
  }
}

int app::run_command(std::string const& command, const std::vector<std::string>& argv) {
  if (command == "list"sv) {
    domain::application_service application_service;
    auto const count = application_service.list();
    out << fmt::format("total: {} issues\n", count);
    return EXIT_SUCCESS;
  }

  if (command == "create"sv) {
    auto const& parsed_args = docopt::docopt_parse(std::string(CREATE_USAGE), argv, false, false, false);
    auto const& title = parsed_args.at("--title").asString();
    auto const& description = parsed_args.at("--descr").asString();

    domain::application_service application_service;
    const auto issue_id = application_service.create(title, description);
    out << fmt::format("Issue created: {}\n", issue_id);
    return EXIT_SUCCESS;
  }

  out << fmt::format("fix: '{}' is not a fix command. See 'fix --help'.\n", command);
  return EXIT_FAILURE;
}
