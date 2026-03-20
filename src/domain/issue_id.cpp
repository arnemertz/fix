#include "issue_id.hpp"

#include <array>
#include <format>
#include <functional>
#include <ranges>
#include <string>

using namespace fix::domain;
namespace rv = std::ranges::views;

namespace {

std::array<std::string, 4> title_segments(title const& t) {
  std::array<std::string, 4> segs{"", "xxx", "yyy", "zzz"};
  std::size_t i = 0;

  for (auto&& word : t.to_string() | rv::split(' ') | rv::take(4)) {
    auto seg = word | rv::take(3)
                    | rv::transform([](char c) { return static_cast<char>(std::tolower(c)); })
                    | std::ranges::to<std::string>();
    if (!seg.empty()) {
      segs[i++] = std::move(seg);
    }
  }

  return segs;
}

std::size_t content_hash(title const& t, description const& d) {
  auto const content = t.to_string() + d.to_string();
  return std::hash<std::string>{}(content) & 0xFFFFFFF; // truncate to 28 bits (7 hex digits)
}

} // namespace

issue_id::issue_id(std::string text) : text{std::move(text)} {}

issue_id issue_id::generate(title const& title, description const& description) {
  auto const segs = title_segments(title);
  auto const hash = content_hash(title, description);
  return issue_id{std::format("{}-{}-{}-{}-{:07x}", segs[0], segs[1], segs[2], segs[3], hash)};
}

std::string const& issue_id::to_string() const {
  return text;
}
