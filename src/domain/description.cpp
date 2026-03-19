#include "description.hpp"

#include <string>

using namespace fix::domain;

namespace {
std::string trim(std::string_view text) {
  auto const start = text.find_first_not_of(" \t\n\r\f\v");
  if (start == std::string_view::npos) {
    return "";
  }
  auto const end = text.find_last_not_of(" \t\n\r\f\v");
  return std::string{text.substr(start, end - start + 1)};
}
} // namespace

description::description(std::string_view text) : text{text} {}

expected<description> description::create(std::string_view text) {
  auto const trimmed = trim(text);
  if (trimmed.empty()) {
    return unexpected(domain_error::DESCRIPTION_EMPTY);
  }
  return description{trimmed};
}

std::string const& description::to_string() const {
  return text;
}
