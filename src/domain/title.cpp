#include "title.hpp"

#include <cctype>
#include <climits>
#include <range/v3/algorithm/any_of.hpp>

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

  if (ranges::any_of(text, [](int c) { return (c > CHAR_MAX) || (c < 0); })) {
    return unexpected(domain_error::TITLE_HAS_NON_ASCII_CHARS);
  }
  if (ranges::any_of(text, [](char c) { return std::isprint(c) == 0; })) {
    return unexpected(domain_error::TITLE_HAS_NON_PRINTABLES);
  }
  if (text.find_first_of("\\`") != std::string_view::npos) {
    return unexpected(domain_error::TITLE_HAS_SPECIAL_PUNCTUATION);
  }

  return title{};
}

std::string title::str() const { // NOLINT
  return "just some normal title";
}
