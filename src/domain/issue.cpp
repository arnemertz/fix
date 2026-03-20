#include "issue.hpp"

#include <string>

using namespace fix::domain;

issue::issue(issue_id id, title title, description description)
    : id_{std::move(id)}, title_{std::move(title)}, description_{std::move(description)} {}

expected<issue> issue::create(std::string_view title_text, std::string_view description_text) {
  auto const title_result = title::create(title_text);
  auto const description_result = description::create(description_text);

  // Validate both and return first error (title takes precedence)
  // The CLI layer can call title::create and description::create separately
  // if it wants to collect all errors
  if (!title_result) {
    return std::unexpected(title_result.error());
  }

  if (!description_result) {
    return std::unexpected(description_result.error());
  }

  auto id = issue_id::generate(*title_result, *description_result);
  return issue{std::move(id), std::move(*title_result), std::move(*description_result)};
}

issue_id const& issue::id() const {
  return id_;
}

title const& issue::get_title() const {
  return title_;
}

description const& issue::get_description() const {
  return description_;
}
