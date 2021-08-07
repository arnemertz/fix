#include <catch2/catch.hpp>

#include <fmt/core.h>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
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

auto split(std::string_view sv) {
  // clang-format off
  return sv
      | ranges::views::split(' ')
      | ranges::views::transform([](auto&& range) {
          return std::string_view{&*range.begin(), size_t(ranges::distance(range))};
        })
      | ranges::to<std::vector>;
  // clang-format on
}

} // namespace

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

  const auto argv = GENERATE(split("foo"), split("bar baz"), split("fruits: apple banana cherries"));

  CHECK(app.run(argv) == EXIT_FAILURE);
  CHECK(out.str() == fmt::format("fix: '{}' is not a fix command. See 'fix --help'.\n", argv.front()));
}

TEST_CASE("List command prints number of issues") {
  std::stringstream out;
  fix::cli::app app{out};

  CHECK(app.run({"list"sv}) == EXIT_SUCCESS);
  CHECK(out.str() == "total: 0 issues\n");
}
