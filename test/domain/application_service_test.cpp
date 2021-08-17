#include <catch2/catch.hpp>

#include "application_service.hpp"

#include <string>
#include <tuple>
using namespace std::literals;

using fix::domain::application_service;

TEST_CASE("Create issue returns issue ID") {
  application_service application_service;
  auto const& [title, description, id_prefix]
      = GENERATE(std::tuple("this is a new issue", "some text", "thi-is-a-new"),
                 std::tuple("My first issue in Fix", "Dorem Fixum dolor sit amet", "my-fir-iss-in"));
  auto const id_pattern = id_prefix + "-[0-9a-f]{7}"s;
  CHECK_THAT(application_service.create(title, description), Catch::Matches(id_pattern));
}

TEST_CASE("List issues returns number of issues") {
  application_service application_service;
  CHECK(application_service.list() == 0);
}