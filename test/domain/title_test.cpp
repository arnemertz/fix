#include "title.hpp"

#include <catch2/catch.hpp>
#include <string>

#include "catch2_expected_matcher.hpp"

using fix::domain::title;
using namespace std::literals;

TEST_CASE("Public construction of titles is only possible via copy, move") {
  STATIC_REQUIRE(std::is_copy_constructible_v<title>);
  STATIC_REQUIRE(std::is_move_constructible_v<title>);

  STATIC_REQUIRE_FALSE(std::is_default_constructible_v<title>);
  STATIC_REQUIRE_FALSE(std::is_constructible_v<title, std::string_view>);
}

TEST_CASE("Titles can be converted back to strings") {
  auto const title_text = GENERATE("just some normal title"sv, "another title"sv);
  auto const title = title::create(title_text);
  CHECK(title->to_string() == title_text);
}

TEST_CASE("Titles have restricted length") {
  SECTION("titles may not be empty") {
    CHECK_THAT(title::create(""), FailsWithMessage("Title is empty"));
  }
  SECTION("titles may not be too short") {
    auto const& short_string = std::string(title::MIN_LENGTH - 1, 's');
    CHECK_THAT(title::create(short_string), FailsWithMessage("title is too short"));
  }
  SECTION("titles may not be too long") {
    auto const long_scream = std::string(title::MAX_LENGTH, 'a') + "h"s;
    CHECK_THAT(title::create(long_scream), FailsWithMessage("title is too long"));
  }
  SECTION("titles with a length in the allowed range can be created") {
    auto const valid_string = GENERATE(std::string(title::MIN_LENGTH, 'n'), std::string(title::MAX_LENGTH, 'x'),
                                       "some title with sufficient length"s);
    auto const title = title::create(valid_string);
    CHECK(title);
  }
}

TEST_CASE("Titles have a restricted character set") {
  SECTION("titles may contain alphanumeric characters and spaces") {
    CHECK(title::create("some VALID_CHARACTERS and 18583075 numbers"));
  }
  SECTION("titles may not contain line breaks and other non-space whitespace") {
    auto const non_space_whitespace = GENERATE("\t"s, "\n", "\r", "\v", "\f");
    CHECK_THAT(title::create("title with a "s + non_space_whitespace + " character"),
               FailsWithMessage("title can only contain letters, digits, and punctuation"));
  }
  SECTION("titles may not contain special punctuation characters") {
    SECTION("backslash") {
      CHECK_THAT(title::create("problematic \\ backslash"), FailsWithMessage("title may not contain '\\' or '`'"));
    }
    SECTION("backtick") {
      CHECK_THAT(title::create("no `backticks` please"), FailsWithMessage("title may not contain '\\' or '`'"));
    }
  }
  SECTION("titles may contain other punctuation characters") {
    CHECK(title::create("the $*@=%<> characters are \"fine\"! (really.) []{ return a?1:~0; }"));
  }
  SECTION("titles may not contain backspace characters") {
    CHECK_THAT(title::create("with a \backspace"),
               FailsWithMessage("title can only contain letters, digits, and punctuation"));
  }
  SECTION("titles may not contain non-ASCII characters") {
    CHECK_THAT(title::create("we \xE2\x99\xA5 unicode. Not."),
               FailsWithMessage("title may not contain non-ASCII characters"));
  }
}

TEST_CASE("Title text is trimmed of leading and trailing whitespace") {
  SECTION("leading and trailing spaces are removed") {
    auto const result = title::create("  some title  ");
    REQUIRE(result);
    CHECK(result->to_string() == "some title");
  }
  SECTION("whitespace-only title is empty after trimming") {
    CHECK_THAT(title::create("   "), FailsWithMessage("Title is empty"));
  }
  SECTION("empty title fails validation") {
    CHECK_THAT(title::create(""), FailsWithMessage("Title is empty"));
  }
}
