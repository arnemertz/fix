#include "description.hpp"

using namespace fix::domain;

description::description(std::string_view text) : text{text} {}

std::string const& description::to_string() const {
  return text;
}
