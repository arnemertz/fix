#ifndef FIX_SRC_DOMAIN_ISSUE_HPP
#define FIX_SRC_DOMAIN_ISSUE_HPP

#include "description.hpp"
#include "domain_error.hpp"
#include "issue_id.hpp"
#include "title.hpp"

namespace fix::domain {

class issue {
  issue_id id_;
  title title_;
  description description_;

  issue(issue_id id, title title, description description);

public:
  // move-only; rule of 5
  issue(issue const&) = delete;
  issue(issue&&) = default;
  issue& operator=(issue const&) = delete;
  issue& operator=(issue&&) = default;
  ~issue() = default;

  static expected<issue> create(std::string_view title_text, std::string_view description_text);

  issue_id const& id() const;
  title const& get_title() const;
  description const& get_description() const;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_ISSUE_HPP
