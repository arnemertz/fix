#ifndef FIX_SRC_DOMAIN_DOMAIN_ERROR_HPP
#define FIX_SRC_DOMAIN_DOMAIN_ERROR_HPP

#include <system_error>
#include <tl/expected.hpp>

namespace fix::domain {

enum class domain_error {
  MISSING_IMPLEMENTATION = 1,
  TITLE_LENGTH_OUT_OF_BOUNDS = 10,
};

template <typename T>
using expected = tl::expected<T, std::error_code>;

inline auto unexpected(domain_error error) {
  return tl::unexpected(error);
}

}

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
