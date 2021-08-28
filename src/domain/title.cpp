#include "title.hpp"

#include <cctype>
#include <climits>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/trim.hpp>

using namespace fix::domain;

constexpr size_t MIN_LENGTH = 6;
constexpr size_t MAX_LENGTH = 120;

namespace {
expected<std::string_view> check_trimmed(std::string_view text);
expected<std::string_view> check_length(std::string_view text);
expected<std::string_view> check_charset(std::string_view text);
} // namespace

title::title(std::string_view text) : text{text} {}

expected<title> title::create(std::string_view text) {
  // clang-format off
  return check_trimmed(text)
      .and_then(check_length)
      .and_then(check_charset)
      .map([](auto text){ return title{text}; });
  // clang-format on
}

std::string title::to_string() const {
  return text;
}

namespace {
expected<std::string_view> check_trimmed(std::string_view text) {
  const auto trimmed_length = ranges::size(text | ranges::views::trim([](char c) { return isspace(c); }));
  if (trimmed_length != text.length()) {
    return unexpected(domain_error::TITLE_NOT_TRIMMED);
  }
  return text;
}

expected<std::string_view> check_length(std::string_view text) {
  if (text.length() < MIN_LENGTH) {
    return unexpected(domain_error::TITLE_TOO_SHORT);
  }
  if (text.length() > MAX_LENGTH) {
    return unexpected(domain_error::TITLE_TOO_LONG);
  }
  return text;
}

expected<std::string_view> check_charset(std::string_view text) {
  if (ranges::any_of(text, [](int c) { return (c > CHAR_MAX) || (c < 0); })) {
    return unexpected(domain_error::TITLE_HAS_NON_ASCII_CHARS);
  }
  if (ranges::any_of(text, [](char c) { return std::isprint(c) == 0; })) {
    return unexpected(domain_error::TITLE_HAS_NON_PRINTABLES);
  }
  if (text.find_first_of("\\`") != std::string_view::npos) {
    return unexpected(domain_error::TITLE_HAS_SPECIAL_PUNCTUATION);
  }
  return text;
}

} // namespace
