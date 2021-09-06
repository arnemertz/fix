#include <catch2/catch.hpp>

#include "description.hpp"

#include <string>
#include <type_traits>

using fix::domain::description;
using namespace std::literals;

TEST_CASE("Descriptions can be copied and moved, but not default-constructed") {
  STATIC_REQUIRE(std::is_copy_constructible_v<description>);
  STATIC_REQUIRE(std::is_move_constructible_v<description>);

  STATIC_REQUIRE_FALSE(std::is_default_constructible_v<description>);
}

TEST_CASE("Descriptions can be created from any string") {
  auto const description_text = GENERATE(""s, "any string"s, std::string(4000, '\1'));
  REQUIRE_NOTHROW(description{description_text});
}

TEST_CASE("Descriptions can be converted back to strings") {
  auto const description_text = GENERATE(
      "some description"s, "the description:\n\t- line breaks are allowed\n\t- and other formatting as well"s);
  auto const the_description = description{description_text};
  CHECK(the_description.to_string() == description_text);
}
