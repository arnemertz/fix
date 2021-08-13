#include "application_service.hpp"

using namespace fix::domain;

std::string application_service::create(std::string_view title, std::string_view description) { // NOLINT
  (void) title;
  (void) description;
  return "thi-is-a-new-0000000";
}
