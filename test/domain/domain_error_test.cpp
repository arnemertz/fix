#include <catch2/catch.hpp>

#include "domain_error.hpp"

using namespace fix::domain;

TEST_CASE("Domain errors can be used with std::error_code") {
  std::error_code error_code = domain_error::MISSING_IMPLEMENTATION;

  CHECK(error_code.message() == "feature is not implemented yet");
}
