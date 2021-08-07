#include <catch2/catch.hpp>

#include <fmt/core.h>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
#include <sstream>
#include <string_view>

#include "app.hpp"

using namespace std::literals;
using fix::cli::app;

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

struct run_result {
  std::string output;
  decltype(std::declval<app>().run({})) exit_code;
};

run_result run_app(std::string_view args) {
  std::stringstream out;
  app app{out};
  auto const exit_code = app.run(split(args));
  return {out.str(), exit_code};
}

} // namespace

TEST_CASE("Prints usage and commands...") {
  SECTION("... when run without commands") {
    auto const [output, exit_code] = run_app("");

    CHECK(output == USAGE);
    CHECK(exit_code == EXIT_FAILURE);
  }
  SECTION("... when run with --help or -h option") {
    auto const args = GENERATE("--help"sv, "-h"sv);
    auto const [output, exit_code] = run_app(args);

    CHECK(output == USAGE);
    CHECK(exit_code == EXIT_SUCCESS);
  }
}

TEST_CASE("Prints 'not a command' ...") {
  auto const args = GENERATE("foo"sv, "bar baz"sv, "fruits: apple banana cherries"sv);
  auto const [output, exit_code] = run_app(args);

  CHECK(output == fmt::format("fix: '{}' is not a fix command. See 'fix --help'.\n", split(args).front()));
  CHECK(exit_code == EXIT_FAILURE);
}

TEST_CASE("List command prints number of issues") {
  auto const [output, exit_code] = run_app("list");

  CHECK(output == "total: 0 issues\n");
  CHECK(exit_code == EXIT_SUCCESS);
}
