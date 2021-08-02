#include <catch2/catch.hpp>

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
    app.run({});
  }SECTION("... when run with --help option") {
    app.run({"--help"});
  }SECTION("... when run with -h option") {
    app.run({"-h"});
  }

  CHECK(out.str() == USAGE);
}
