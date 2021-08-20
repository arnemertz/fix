#ifndef FIX_SRC_DOMAIN_TITLE_HPP
#define FIX_SRC_DOMAIN_TITLE_HPP

#include <string_view>

namespace fix::domain {

class title {
public:
  static bool create(std::string_view str);
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_TITLE_HPP
