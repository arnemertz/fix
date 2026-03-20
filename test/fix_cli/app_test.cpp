#include "app.hpp"

#include <catch2/catch.hpp>
#include <format>
#include <ranges>
#include <sstream>
#include <string_view>

#include "issue.hpp"
#include "issue_service.hpp"

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

// Minimal fake: create() delegates to domain logic for ID generation;
// list() returns an empty list. No repository, no filesystem.
struct stub_issue_service : fix::domain::issue_service {
  fix::domain::expected<std::string> create(std::string_view title,
                                            std::string_view description) override {
    auto result = fix::domain::issue::create(title, description);
    if (!result) return std::unexpected(result.error());
    return result->id().to_string();
  }

  fix::domain::expected<std::vector<fix::domain::issue>> list() const override {
    return std::vector<fix::domain::issue>{};
  }
};

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

run_result run_app(fix::domain::issue_service& service, std::vector<std::string> argv) {
  argv.insert(argv.begin(), "fix");

  std::vector<char const*> argv_ptrs;
  argv_ptrs.reserve(argv.size());
  for (auto const& arg : argv) {
    argv_ptrs.push_back(arg.c_str());
  }

  std::stringstream out;
  app app{out, service};
  auto const exit_code = app.run(static_cast<int>(argv_ptrs.size()), argv_ptrs.data());
  return {out.str(), exit_code};
}

run_result run_app(fix::domain::issue_service& service, std::string_view args) {
  return run_app(service, split(args));
}

// Overload for tests that don't exercise repository behaviour
run_result run_app(std::vector<std::string> argv) {
  stub_issue_service stub;
  return run_app(stub, std::move(argv));
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
