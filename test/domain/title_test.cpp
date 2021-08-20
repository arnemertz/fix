#include <catch2/catch.hpp>

#include "title.hpp"

using fix::domain::title;

TEST_CASE("Titles have restricted length") {
  SECTION("titles may not be empty") {
    CHECK_FALSE(title::create(""));
  }

  SECTION("titles may not be too short") {}
  SECTION("titles may not be too long") {}
  SECTION("titles with a length in the allowed range can be created") {}
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
