#ifndef FIX_SRC_DOMAIN_TEXT_UTILS_HPP
#define FIX_SRC_DOMAIN_TEXT_UTILS_HPP

#include <string_view>

namespace fix::domain {

inline std::string_view trim(std::string_view text) {
  static constexpr std::string_view whitespace_chars = " \t\n\r\f\v";
  auto const start = text.find_first_not_of(whitespace_chars);
  if (start == std::string_view::npos) {
    return {};
  }
  auto const end = text.find_last_not_of(whitespace_chars);
  return text.substr(start, end - start + 1);
}

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_TEXT_UTILS_HPP
