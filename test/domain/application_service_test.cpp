#include <catch2/catch.hpp>

#include "application_service.hpp"

using fix::domain::application_service;

TEST_CASE("Create issue returns issue ID") {
  application_service application_service;
  CHECK_THAT(application_service.create("this is a new issue", "some text"), Catch::Matches("thi-is-a-new-[0-9a-f]{7}"));
}
