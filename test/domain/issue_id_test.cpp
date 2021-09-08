#include <catch2/catch.hpp>

#include "issue_id.hpp"

#include <string>

#include "description.hpp"
#include "title.hpp"

using namespace fix::domain;
using namespace std::literals;

TEST_CASE("Issue IDs can be moved, but not default-constructed or copied") {
  STATIC_REQUIRE(std::is_move_constructible_v<issue_id>);

  STATIC_REQUIRE_FALSE(std::is_copy_assignable_v<issue_id>);
  STATIC_REQUIRE_FALSE(std::is_copy_constructible_v<issue_id>);
  STATIC_REQUIRE_FALSE(std::is_default_constructible_v<issue_id>);
}

TEST_CASE("Issue ID is contains abbreviated first words of the title") {
  auto const& [the_title, the_description, id_prefix] = GENERATE(
      std::tuple(title::create("this is a new issue"), description{"some text"}, "thi-is-a-new"),
      std::tuple(title::create("My first issue in Fix"), description{"Dorem Fixum dolor sit amet"}, "my-fir-iss-in"));

  REQUIRE(the_title);

  auto const id_pattern = id_prefix + "-[0-9a-f]{7}"s;
  CHECK_THAT(issue_id::generate(the_title.value(), the_description).to_string(), Catch::Matches(id_pattern));
}
