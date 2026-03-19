#include "issue_id.hpp"

#include <array>
#include <format>
#include <functional>
#include <ranges>
#include <string>

using namespace fix::domain;
namespace rv = std::ranges::views;

issue_id::issue_id(std::string text) : text{std::move(text)} {}

issue_id issue_id::generate(title const& title, description const& description) {
  // Padding segments used when title has fewer than 4 words
  static constexpr std::array<std::string_view, 3> padding{"xxx", "yyy", "zzz"};

  // Extract up to 4 three-char lowercased word abbreviations from title
  std::vector<std::string> segments;
  for (auto&& word : title.to_string() | rv::split(' ') | rv::take(4)) {
    auto seg = word | rv::take(3)
                    | rv::transform([](char c) { return static_cast<char>(std::tolower(c)); })
                    | std::ranges::to<std::string>();
    if (!seg.empty()) {
      segments.push_back(std::move(seg));
    }
  }

  // Pad to 4 segments with xxx/yyy/zzz
  std::size_t const pads_needed = 4 - std::min<std::size_t>(4, segments.size());
  std::size_t const pad_start = padding.size() - pads_needed;
  for (std::size_t i = pad_start; i < padding.size(); ++i) {
    segments.emplace_back(padding[i]);
  }

  // Join segments with hyphens
  std::string id_prefix;
  for (auto const& seg : segments) {
    if (!id_prefix.empty()) id_prefix += '-';
    id_prefix += seg;
  }

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
