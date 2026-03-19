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
      std::tuple(title::create("this is a new issue"), description::create("some text"), "thi-is-a-new"),
      std::tuple(title::create("My first issue in Fix"), description::create("Dorem Fixum dolor sit amet"), "my-fir-iss-in"));

  REQUIRE(the_title);
  REQUIRE(the_description);

  auto const id_pattern = id_prefix + "-[0-9a-f]{7}"s;
  CHECK_THAT(issue_id::generate(the_title.value(), the_description.value()).to_string(), Catch::Matches(id_pattern));
}

TEST_CASE("Issue ID prefix is padded with xxx/yyy/zzz for short titles") {
  auto const desc = description::create("some description");
  REQUIRE(desc);

  SECTION("one word pads with xxx-yyy-zzz") {
    auto const t = title::create("Minimum");
    REQUIRE(t);
    auto id = issue_id::generate(*t, *desc);
    CHECK_THAT(id.to_string(), Catch::Matches("min-xxx-yyy-zzz-[0-9a-f]{7}"));
  }
  SECTION("two words pads with yyy-zzz") {
    auto const t = title::create("Two words");
    REQUIRE(t);
    auto id = issue_id::generate(*t, *desc);
    CHECK_THAT(id.to_string(), Catch::Matches("two-wor-yyy-zzz-[0-9a-f]{7}"));
  }
  SECTION("three words pads with zzz") {
    auto const t = title::create("Three word title");
    REQUIRE(t);
    auto id = issue_id::generate(*t, *desc);
    CHECK_THAT(id.to_string(), Catch::Matches("thr-wor-tit-zzz-[0-9a-f]{7}"));
  }
  SECTION("four or more words - no padding") {
    auto const t = title::create("Four words in title");
    REQUIRE(t);
    auto id = issue_id::generate(*t, *desc);
    CHECK_THAT(id.to_string(), Catch::Matches("fou-wor-in-tit-[0-9a-f]{7}"));
  }
}

TEST_CASE("Issue ID hash is deterministic") {
  auto const title1 = title::create("Test title");
  auto const desc1 = description::create("Test description");

  auto const id1 = issue_id::generate(*title1, *desc1).to_string();
  auto const id2 = issue_id::generate(*title1, *desc1).to_string();

  CHECK(id1 == id2);
}

TEST_CASE("Issue ID hash differentiates issues") {
  auto const title1 = title::create("Same title");
  auto const desc1 = description::create("Description one");
  auto const desc2 = description::create("Description two");

  auto id1 = issue_id::generate(*title1, *desc1);
  auto id2 = issue_id::generate(*title1, *desc2);

  CHECK(id1.to_string() != id2.to_string());
}
