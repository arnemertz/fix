#include "issue_id.hpp"

#include <format>
#include <functional>
#include <ranges>

using namespace fix::domain;
using namespace std::literals;
namespace rv = std::ranges::views;

issue_id::issue_id(std::string text) : text{std::move(text)} {}

issue_id issue_id::generate(title const& title, description const& description) {
  // Generate prefix from title
  // clang-format off
  auto const id_prefix = title.to_string()
      | rv::split(' ')
      | rv::take(4)
      | rv::transform([](auto&& word) {
        return word | rv::take(3) | rv::transform([](char c){ return static_cast<char>(std::tolower(c)); });
      })
      | rv::join_with('-')
      | std::ranges::to<std::string>();
  // clang-format on

  // Compute hash from title + description (already trimmed by value object constructors)
  auto const content = title.to_string() + description.to_string();
  auto const hash_value = std::hash<std::string>{}(content);

  // Truncate to 7 hex digits (28 bits)
  auto const truncated_hash = hash_value & 0xFFFFFFF;
  auto const hash_string = std::format("{:07x}", truncated_hash);

  return issue_id{id_prefix + "-" + hash_string};
}

std::string const& issue_id::to_string() const {
  return text;
}
