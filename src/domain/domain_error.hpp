#ifndef FIX_SRC_DOMAIN_DOMAIN_ERROR_HPP
#define FIX_SRC_DOMAIN_DOMAIN_ERROR_HPP

#include <expected>
#include <system_error>

namespace fix::domain {

// Error codes are grouped by category, each occupying a reserved numeric range
// (e.g. 1–9 general, 10–19 title, 20–29 description) to leave room for future additions.
enum class domain_error {
  MISSING_IMPLEMENTATION = 1,
  TITLE_TOO_LONG = 10,
  TITLE_TOO_SHORT = 11,
  TITLE_HAS_NON_PRINTABLES = 12,
  TITLE_HAS_SPECIAL_PUNCTUATION = 13,
  TITLE_HAS_NON_ASCII_CHARS = 14,
  TITLE_NOT_TRIMMED = 15,
  TITLE_EMPTY = 16,
  DESCRIPTION_EMPTY = 20,
};

template<typename T>
using expected = std::expected<T, std::error_code>;

inline auto unexpected(domain_error error) {
  return std::unexpected(error);
}

} // namespace fix::domain

// =========================================================
// wiring to enable use of std::error_code with domain_error
// =========================================================
namespace std {
template<>
struct is_error_code_enum<fix::domain::domain_error> : true_type {};
} // namespace std

namespace fix::domain {
std::error_code make_error_code(domain_error);
}

#endif // FIX_SRC_DOMAIN_DOMAIN_ERROR_HPP
