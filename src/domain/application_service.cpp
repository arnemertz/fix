#include "application_service.hpp"

#include <string>

#include "description.hpp"
#include "issue_id.hpp"
#include "title.hpp"

using namespace fix::domain;
using namespace std::literals;

std::string application_service::create(std::string_view title, std::string_view description) { // NOLINT
  auto const the_title = title::create(title);
  if (!the_title) {
    return ""; // TODO: proper error handling
  }

  const auto issue_id = issue_id::generate(*the_title, fix::domain::description(description));
  return issue_id.to_string();
}

size_t application_service::list() const { // NOLINT
  return 0;
}
