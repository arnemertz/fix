#include <catch2/catch.hpp>
#include <string_view>

#include "catch2_expected_matcher.hpp"
#include "domain_error.hpp"

using namespace fix::domain;
using namespace std::literals;

TEST_CASE("Domain errors can be used with std::error_code") {
  std::error_code error_code = domain_error::MISSING_IMPLEMENTATION;

  CHECK(error_code.message() == "feature is not implemented yet"sv);
  CHECK(error_code.category().name() == "fix domain error"sv);
}

namespace {
  expected<void> fails_not_implemented() {
    return unexpected(domain_error::MISSING_IMPLEMENTATION);
  }

  expected<int> succeeds() {
    return 1;
  }
}

TEST_CASE("The Catch2 matcher for fix::domain::expected recognizes error state and message") {
  CHECK_THAT(fails_not_implemented(), FailsWithMessage("feature is not implemented yet"sv));
  CHECK_THAT(fails_not_implemented(), ! FailsWithMessage("wrong message"));
  CHECK_THAT(succeeds(), ! FailsWithMessage("success is not failure"));
}
