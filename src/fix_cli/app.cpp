#include "app.hpp"

#include <fmt/core.h>
#include <ostream>

using namespace fix::cli;
using namespace std::string_view_literals;

namespace {
constexpr auto USAGE = R"(usage: fix [--help] <command> [<args>]

Available commands:
   create        Create a new issue
   setstatus     Set the status of an issue
   list          List all existing issues
   show          Show a specific issue
)"sv;
}

app::app(std::ostream& out) : out{out} {}

auto app::run(const std::vector<std::string_view>& args) -> int { // NOLINT
  if (args.empty()) {
    out << USAGE;
    return EXIT_FAILURE;
  }

  if (args[0] == "--help"sv || args[0] == "-h"sv) {
    out << USAGE;
    return EXIT_SUCCESS;
  }

  out << fmt::format("fix: '{}' is not a fix command. See 'fix --help'.\n", args[0]);
  return EXIT_FAILURE;
}
