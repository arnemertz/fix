#ifndef FIX_SRC_DOMAIN_DESCRIPTION_HPP
#define FIX_SRC_DOMAIN_DESCRIPTION_HPP

#include <string>
#include <string_view>

#include "domain_error.hpp"

namespace fix::domain {

class description {
  std::string text;

public:
  explicit description(std::string_view text);
  std::string const& to_string() const;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_DESCRIPTION_HPP
