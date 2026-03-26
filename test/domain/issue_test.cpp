#include "issue.hpp"

#include <catch2/catch.hpp>
#include <string>

#include "catch2_expected_matcher.hpp"
#include "description.hpp"
#include "issue_id.hpp"
#include "title.hpp"

using fix::domain::description;
using fix::domain::issue;
using fix::domain::issue_id;
using fix::domain::title;
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
  CHECK_THAT(issue::create("", ""), FailsWithMessage("Title is empty"));
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
  auto const the_title = title::create("Test title");
  auto const the_description = description::create("Test description");
  REQUIRE(the_title);
  REQUIRE(the_description);

  auto const expected_id = issue_id::generate(*the_title, *the_description).to_string();
  auto const result = issue::create("Test title", "Test description");
  REQUIRE(result);

  CHECK(result->id().to_string() == expected_id);
}
