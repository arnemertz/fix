#ifndef FIX_DOMAIN_APPLICATION_SERVICE_HPP
#define FIX_DOMAIN_APPLICATION_SERVICE_HPP

#include <string>

namespace fix::domain {

class application_service {
public:
  // cppcheck-suppress functionStatic
  std::string create(std::string_view title, std::string_view description);

  // cppcheck-suppress functionStatic
  size_t list() const;
};

}

#endif // FIX_DOMAIN_APPLICATION_SERVICE_HPP
