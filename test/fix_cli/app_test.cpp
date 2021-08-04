#include <catch2/catch.hpp>

#include <fmt/core.h>
#include <sstream>
#include <string_view>

#include "app.hpp"

using namespace std::literals;

namespace {
constexpr auto USAGE = R"(usage: fix [--help] <command> [<args>]

Available commands:
   create        Create a new issue
   setstatus     Set the status of an issue
   list          List all existing issues
   show          Show a specific issue
)"sv;
}

TEST_CASE("Prints usage and commands...") {
  std::stringstream out;
  fix::cli::app app{out};

  SECTION("... when run without commands") {
    CHECK(app.run({}) == EXIT_FAILURE);
  }
  SECTION("... when run with --help option") {
    CHECK(app.run({"--help"}) == EXIT_SUCCESS);
  }
  SECTION("... when run with -h option") {
    CHECK(app.run({"-h"}) == EXIT_SUCCESS);
  }

  CHECK(out.str() == USAGE);
}

TEST_CASE("Prints 'not a command' ...") {
  std::stringstream out;
  fix::cli::app app{out};

  const auto argv = GENERATE(std::vector{"foo"sv}, std::vector{"bar"sv, "baz"sv},
                             std::vector{"fruits:"sv, "apple"sv, "banana"sv, "cherries"sv});

  CHECK(app.run(argv) == EXIT_FAILURE);
  CHECK(out.str() == fmt::format("fix: '{}' is not a fix command. See 'fix --help'.\n", argv.front()));
}
