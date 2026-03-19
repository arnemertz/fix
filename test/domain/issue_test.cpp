#include <catch2/catch.hpp>

#include "issue.hpp"

#include "catch2_expected_matcher.hpp"
#include <string>

using fix::domain::issue;
using namespace std::literals;

TEST_CASE("Issues can be moved, but not copied or default-constructed") {
  STATIC_REQUIRE(std::is_move_constructible_v<issue>);

  STATIC_REQUIRE_FALSE(std::is_copy_constructible_v<issue>);
  STATIC_REQUIRE_FALSE(std::is_default_constructible_v<issue>);
}

TEST_CASE("Issue can be created with valid title and description") {
  auto const result = issue::create("Valid title", "Valid description");
  REQUIRE(result);
  
  CHECK(result->get_title().to_string() == "Valid title");
  CHECK(result->get_description().to_string() == "Valid description");
}

TEST_CASE("Issue creation trims title and description") {
  auto const result = issue::create("  Trimmed title  ", "  Trimmed description  ");
  REQUIRE(result);
  
  CHECK(result->get_title().to_string() == "Trimmed title");
  CHECK(result->get_description().to_string() == "Trimmed description");
}

TEST_CASE("Issue creation fails with empty title") {
  CHECK_THAT(issue::create("", "Valid description"), FailsWithMessage("Title is empty"));
}

TEST_CASE("Issue creation fails with empty description") {
  CHECK_THAT(issue::create("Valid title", ""), FailsWithMessage("Description is empty"));
}

TEST_CASE("Issue creation with both empty returns title error first") {
  auto const result = issue::create("", "");
  REQUIRE_FALSE(result);

  // When both fail, title error is returned (validated first)
  CHECK(result.error().message().find("Title is empty") != std::string::npos);
}

TEST_CASE("Issue creation with whitespace-only inputs fails") {
  SECTION("whitespace-only title") {
    CHECK_THAT(issue::create("   ", "Valid description"), FailsWithMessage("Title is empty"));
  }
  SECTION("whitespace-only description") {
    CHECK_THAT(issue::create("Valid title", "   "), FailsWithMessage("Description is empty"));
  }
}

TEST_CASE("Issue has an ID generated from title and description") {
  auto const result = issue::create("Test title", "Test description");
  REQUIRE(result);
  
  CHECK_FALSE(result->id().to_string().empty());
}
