#include "app.hpp"

#include <docopt/docopt.h>
#include <fmt/core.h>
#include <ostream>

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
}

app::app(std::ostream& out) : out{out} {}

auto app::run(const std::vector<std::string_view>& args) -> int {
  std::vector<std::string> const argv(args.begin(), args.end());

  try {
    auto const& parsed_args = docopt::docopt_parse(std::string(USAGE), argv, true, false, true);
    auto const& command = parsed_args.at("<command>").asString();

    if (command == "list"sv) {
      out << "total: 0 issues\n";
      return EXIT_SUCCESS;
    }

    out << fmt::format("fix: '{}' is not a fix command. See 'fix --help'.\n", command);
    return EXIT_FAILURE;

  } catch (docopt::DocoptExitHelp const&) {
    out << USAGE;
    return EXIT_SUCCESS;

  } catch (docopt::DocoptArgumentError& argError) {
    out << USAGE;
    return EXIT_FAILURE;
  }
}
