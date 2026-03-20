#include "application_service.hpp"

#include <string>

#include "description.hpp"
#include "issue.hpp"
#include "issue_id.hpp"
#include "title.hpp"

using namespace fix::domain;
using namespace std::literals;

application_service::application_service(issue_repository& repository) : repository_{repository} {}

expected<std::string> application_service::create(std::string_view title, std::string_view description) {
  // Create issue (validates title and description)
  auto issue_result = issue::create(title, description);
  if (!issue_result) {
    return std::unexpected(issue_result.error());
  }

  // Check for duplicate
  if (repository_.exists(issue_result->id())) {
    return std::unexpected(std::make_error_code(std::errc::file_exists));
  }

  // Save issue
  auto save_result = repository_.save(*issue_result);
  if (!save_result) {
    return std::unexpected(save_result.error());
  }

  return issue_result->id().to_string();
}

expected<std::vector<issue>> application_service::list() const {
  return repository_.find_all();
}
