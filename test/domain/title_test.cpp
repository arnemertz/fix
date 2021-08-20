#include <catch2/catch.hpp>

#include "title.hpp"

#include <string>

using fix::domain::title;
using namespace std::literals;

constexpr size_t MIN_LENGTH = 6;
constexpr size_t MAX_LENGTH = 120;

TEST_CASE("Titles have restricted length") {
  SECTION("titles may not be empty") {
    CHECK_FALSE(title::create(""));
  }
  SECTION("titles may not be too short") {
    CHECK_FALSE(title::create("short"));
  }
  SECTION("titles may not be too long") {
    const auto long_scream = std::string(MAX_LENGTH, 'a') + "h"s;
    CHECK_FALSE(title::create(long_scream));
  }
  SECTION("titles with a length in the allowed range can be created") {
    const auto valid_string = GENERATE(std::string(MIN_LENGTH, 'n'), std::string(MAX_LENGTH, 'x'), "some title with sufficient length"s);
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
