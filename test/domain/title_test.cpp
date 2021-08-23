#include <catch2/catch.hpp>

#include "title.hpp"

#include "catch2_expected_matcher.hpp"
#include <string>

using fix::domain::title;
using namespace std::literals;

constexpr size_t MIN_LENGTH = 6;
constexpr size_t MAX_LENGTH = 120;

TEST_CASE("Titles can be converted back to strings") {
  const auto title_text = "just some normal title"sv;
  const auto title = title::create(title_text);
  CHECK(title->str() == title_text);
}

TEST_CASE("Titles have restricted length") {
  SECTION("titles may not be empty") {
    CHECK_THAT(title::create(""), FailsWithMessage("title is too short"));
  }
  SECTION("titles may not be too short") {
    const auto& short_string = std::string(MIN_LENGTH - 1, 's');
    CHECK_THAT(title::create(short_string), FailsWithMessage("title is too short"));
  }
  SECTION("titles may not be too long") {
    auto const long_scream = std::string(MAX_LENGTH, 'a') + "h"s;
    CHECK_THAT(title::create(long_scream), FailsWithMessage("title is too long"));
  }
  SECTION("titles with a length in the allowed range can be created") {
    const auto valid_string
        = GENERATE(std::string(MIN_LENGTH, 'n'), std::string(MAX_LENGTH, 'x'), "some title with sufficient length"s);
    const auto title = title::create(valid_string);
    CHECK(title);
  }
}

TEST_CASE("Titles have a restricted character set") {
  SECTION("titles may contain alphanumeric characters and spaces") {}
  SECTION("titles may not contain line breaks and other non-space whitespace") {}
  SECTION("titles may not contain special punctuation characters") {
    SECTION("backspace") {}
    SECTION("backtick") {}
  }
  SECTION("titles may contain other punctuation characters") {}
  SECTION("titles may not contain backspace characters") {}
  SECTION("titles may not contain non-ASCII characters") {}
}
