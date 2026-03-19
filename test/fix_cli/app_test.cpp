#include <catch2/catch.hpp>

#include <format>
#include <ranges>
#include <sstream>
#include <string_view>

#include "app.hpp"

using namespace std::literals;
using fix::cli::app;


namespace {
constexpr auto USAGE = R"(fix - Issue tracker
Usage: fix [OPTIONS] [SUBCOMMAND]

Options:
  -h,--help                   Print this help message and exit

Subcommands:
  list                        List all existing issues
  create                      Create a new issue
)"sv;

auto split(std::string_view sv) {
  // clang-format off
  return sv
      | std::ranges::views::split(' ')
      | std::ranges::views::transform([](auto&& range) {
          return std::string{&*range.begin(), static_cast<size_t>(std::ranges::distance(range))};
        })
      | std::ranges::to<std::vector>();
  // clang-format on
}

struct run_result {
  std::string output;
  int exit_code;
};

run_result run_app(std::vector<std::string> argv) {
  // Prepend program name
  argv.insert(argv.begin(), "fix");

  // Create argv pointer array from stored strings
  std::vector<char const*> argv_ptrs;
  argv_ptrs.reserve(argv.size());
  for (auto const& arg : argv) {
    argv_ptrs.push_back(arg.c_str());
  }

  std::stringstream out;
  app app{out};
  auto const exit_code = app.run(static_cast<int>(argv_ptrs.size()), argv_ptrs.data());
  return {out.str(), exit_code};
}

run_result run_app(std::string_view args) {
  return run_app(split(args));
}

} // namespace

TEST_CASE("Prints usage...") {
  SECTION("... for --help and -h") {
    auto const args = GENERATE("--help"sv, "-h"sv);
    auto const [output, exit_code] = run_app(args);

    CHECK(output == USAGE);
    CHECK(exit_code == EXIT_SUCCESS);
  }
  SECTION("... when called without arguments") {
    auto const [output, exit_code] = run_app(std::vector<std::string>{});

    CHECK(output == USAGE);
    CHECK(exit_code == EXIT_FAILURE);
  }
}

TEST_CASE("Prints error messages...") {
  SECTION("... for unknown subcommands") {
    auto const args = GENERATE("foo"sv, "bar baz"sv, "fruits: apple banana cherries"sv);
    auto const [output, exit_code] = run_app(args);

    CHECK(output == "fix: unknown subcommand. See 'fix --help'.\n");
    CHECK(exit_code == EXIT_FAILURE);
  }
}

TEST_CASE("List command prints number of issues") {
  auto const [output, exit_code] = run_app("list");

  CHECK(output == "total: 0 issues\n");
  CHECK(exit_code == EXIT_SUCCESS);
}

TEST_CASE("Create issue command prints issue ID") {
  auto const& [title, description, id_prefix]
  = GENERATE(std::tuple("this is a new issue", "some text", "thi-is-a-new"),
             std::tuple("My first issue in Fix", "Dorem Fixum dolor sit amet", "my-fir-iss-in"));

  auto const [output, exit_code] = run_app({"create", "-t", title, "-d", description});

  CHECK_THAT(output, Catch::Matches(std::format("Issue created: {}-[0-9a-f]{{7}}\n", id_prefix)));
  CHECK(exit_code == EXIT_SUCCESS);
}
