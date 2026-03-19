#ifndef FIX_DOMAIN_APPLICATION_SERVICE_HPP
#define FIX_DOMAIN_APPLICATION_SERVICE_HPP

#include "domain_error.hpp"
#include "issue.hpp"
#include "issue_repository.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace fix::domain {

class application_service {
  issue_repository& repository_;

public:
  explicit application_service(issue_repository& repository);

  expected<std::string> create(std::string_view title, std::string_view description);
  expected<std::vector<issue>> list() const;
};

}

#endif // FIX_DOMAIN_APPLICATION_SERVICE_HPP
