#ifndef FIX_SRC_DOMAIN_TITLE_HPP
#define FIX_SRC_DOMAIN_TITLE_HPP

#include <optional>
#include <string>
#include <string_view>

namespace fix::domain {

class title {
public:
  static std::optional<title> create(std::string_view text);

  std::string str() const;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_TITLE_HPP
