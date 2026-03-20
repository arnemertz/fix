#ifndef FIX_SRC_DOMAIN_ISSUE_SERVICE_HPP
#define FIX_SRC_DOMAIN_ISSUE_SERVICE_HPP

#include <string>
#include <string_view>
#include <vector>

#include "domain_error.hpp"
#include "issue.hpp"

namespace fix::domain {

class issue_service {
public:
  virtual ~issue_service() = default;
  virtual expected<std::string> create(std::string_view title, std::string_view description) = 0;
  virtual expected<std::vector<issue>> list() const = 0;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_ISSUE_SERVICE_HPP
