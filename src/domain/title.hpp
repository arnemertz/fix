#ifndef FIX_SRC_DOMAIN_TITLE_HPP
#define FIX_SRC_DOMAIN_TITLE_HPP

#include <cstddef>
#include <string>
#include <string_view>

#include <domain_error.hpp>

namespace fix::domain {

class title {
  std::string text;

  explicit title(std::string_view text);

public:
  static constexpr std::size_t MIN_LENGTH = 6;
  static constexpr std::size_t MAX_LENGTH = 120;

  static expected<title> create(std::string_view text);

  std::string const& to_string() const;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_TITLE_HPP
