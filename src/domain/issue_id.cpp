#include "issue_id.hpp"

#include <ranges>

using namespace fix::domain;
using namespace std::literals;
namespace rv = std::ranges::views;

issue_id::issue_id(std::string text) : text{std::move(text)} {}

issue_id issue_id::generate(title const& title, description const& description) {
  (void)description;
  // clang-format off
  const auto id_prefix = title.to_string()
      | rv::split(' ')
      | rv::take(4)
      | rv::transform([](auto&& word) {
        return word | rv::take(3) | rv::transform([](char c){ return static_cast<char>(std::tolower(c)); });
      })
      | rv::join_with('-')
      | std::ranges::to<std::string>();
  // clang-format on
  return issue_id{id_prefix + "-0000000"s};
}

std::string const& issue_id::to_string() const {
  return text;
}
