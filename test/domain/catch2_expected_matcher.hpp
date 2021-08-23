#ifndef FIX_TEST_DOMAIN_CATCH2_EXPECTED_MATCHER_HPP
#define FIX_TEST_DOMAIN_CATCH2_EXPECTED_MATCHER_HPP

#include "domain_error.hpp"
#include <catch2/catch.hpp>

namespace detail {
struct inspect_expect {
  bool has_value;
  std::error_code error;
  template<typename T>
  // cppcheck-suppress noExplicitConstructor
  inspect_expect(fix::domain::expected<T> const& expected)
      : has_value(expected.has_value()), error(expected ? std::error_code{} : expected.error()) {}
};

} // namespace detail

class FailsWithMessage : public Catch::MatcherBase<detail::inspect_expect> {
  std::string_view message;

public:
  explicit FailsWithMessage(std::string_view message) : message{message} {}

  bool match(detail::inspect_expect const& inspector) const override {
    if (inspector.has_value) {
      return false;
    }
    auto const& error_code = inspector.error;
    return error_code.message() == message;
  }

  std::string describe() const override {
    return std::string("Fails with message '") + std::string(message) + '\'';
  }
};

#endif // FIX_TEST_DOMAIN_CATCH2_EXPECTED_MATCHER_HPP
