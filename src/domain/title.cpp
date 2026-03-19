#include "title.hpp"

#include <algorithm>
#include <cctype>
#include <climits>
#include <string>

using namespace fix::domain;

namespace {
std::string trim(std::string_view text);
expected<std::string_view> check_length(std::string_view text);
expected<std::string_view> check_charset(std::string_view text);
} // namespace

title::title(std::string_view text) : text{text} {}

expected<title> title::create(std::string_view text) {
  auto const trimmed = trim(text);
  auto const make_title = [](auto text) { return title{text}; };
  // clang-format off
  return check_length(trimmed)
      .and_then(check_charset)
      .transform(make_title);
  // clang-format on
}

std::string const& title::to_string() const {
  return text;
}

namespace {
std::string trim(std::string_view text) {
  auto const start = text.find_first_not_of(" \t\n\r\f\v");
  if (start == std::string_view::npos) {
    return "";
  }
  auto const end = text.find_last_not_of(" \t\n\r\f\v");
  return std::string{text.substr(start, end - start + 1)};
}

expected<std::string_view> check_length(std::string_view text) {
  if (text.length() < title::MIN_LENGTH) {
    return unexpected(domain_error::TITLE_TOO_SHORT);
  }
  if (text.length() > title::MAX_LENGTH) {
    return unexpected(domain_error::TITLE_TOO_LONG);
  }
  return text;
}

expected<std::string_view> check_charset(std::string_view text) {
  if (std::ranges::any_of(text, [](int c) { return (c > CHAR_MAX) || (c < 0); })) {
    return unexpected(domain_error::TITLE_HAS_NON_ASCII_CHARS);
  }
  if (std::ranges::any_of(text, [](char c) { return std::isprint(c) == 0; })) {
    return unexpected(domain_error::TITLE_HAS_NON_PRINTABLES);
  }
  if (text.find_first_of("\\`") != std::string_view::npos) {
    return unexpected(domain_error::TITLE_HAS_SPECIAL_PUNCTUATION);
  }
  return text;
}

} // namespace
