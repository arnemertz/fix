#include "title.hpp"

using fix::domain::title;

constexpr size_t MIN_LENGTH = 6;
constexpr size_t MAX_LENGTH = 120;

std::optional<title> title::create(std::string_view text) {
  if ((text.length() < MIN_LENGTH) || (text.length() > MAX_LENGTH)) {
    return std::nullopt;
  }
  return title{};
}

std::string title::str() const { // NOLINT
  return "just some normal title";
}
