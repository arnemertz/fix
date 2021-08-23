#ifndef FIX_SRC_DOMAIN_TITLE_HPP
#define FIX_SRC_DOMAIN_TITLE_HPP

#include <optional>
#include <string>
#include <string_view>

#include <domain_error.hpp>

namespace fix::domain {

class title {
public:
  static expected<title> create(std::string_view text);

  // cppcheck-suppress functionStatic
  std::string str() const;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_TITLE_HPP
