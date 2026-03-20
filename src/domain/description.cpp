#include "description.hpp"

#include "text_utils.hpp"

using namespace fix::domain;

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
