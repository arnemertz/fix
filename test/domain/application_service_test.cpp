#include "application_service.hpp"

#include <catch2/catch.hpp>
#include <string>
#include <tuple>

#include "in_memory_issue_repository.hpp"
using namespace std::literals;

using fix::domain::application_service;
using fix::test::in_memory_issue_repository;

TEST_CASE("Create issue returns issue ID") {
  in_memory_issue_repository repository;
  application_service service{repository};

  auto const& [title, description, id_prefix]
      = GENERATE(std::tuple("this is a new issue", "some text", "thi-is-a-new"),
                 std::tuple("My first issue in Fix", "Dorem Fixum dolor sit amet", "my-fir-iss-in"));

  auto const result = service.create(title, description);
  REQUIRE(result);

  auto const id_pattern = id_prefix + "-[0-9a-f]{7}"s;
  CHECK_THAT(*result, Catch::Matches(id_pattern));
}

TEST_CASE("List issues returns empty list initially") {
  in_memory_issue_repository repository;
  application_service service{repository};

  auto const result = service.list();
  REQUIRE(result);
  CHECK(result->empty());
}

TEST_CASE("Created issues appear in list") {
  in_memory_issue_repository repository;
  application_service service{repository};

  auto const create1 = service.create("First issue", "First description");
  auto const create2 = service.create("Second issue", "Second description");
  REQUIRE(create1);
  REQUIRE(create2);

  auto const result = service.list();
  REQUIRE(result);
  CHECK(result->size() == 2);
}

TEST_CASE("Duplicate issue creation is rejected") {
  in_memory_issue_repository repository;
  application_service service{repository};

  auto const create1 = service.create("Same title", "Same description");
  REQUIRE(create1);

  auto const create2 = service.create("Same title", "Same description");
  CHECK_FALSE(create2);
}