#include "title.hpp"

using namespace fix::domain;

constexpr size_t MIN_LENGTH = 6;
constexpr size_t MAX_LENGTH = 120;

expected<title> title::create(std::string_view text) {
  if (text.length() < MIN_LENGTH) {
    return unexpected(domain_error::TITLE_TOO_SHORT);
  }
  if (text.length() > MAX_LENGTH) {
    return unexpected(domain_error::TITLE_TOO_LONG);
  }

  return title{};
}

std::string title::str() const { // NOLINT
  return "just some normal title";
}
