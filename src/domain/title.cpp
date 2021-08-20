#include "title.hpp"

using fix::domain::title;

constexpr size_t MIN_LENGTH = 6;
constexpr size_t MAX_LENGTH = 120;

bool title::create(std::string_view text) {
  return (text.length() >= MIN_LENGTH) && (text.length() <= MAX_LENGTH);
}
