#ifndef FIX_SRC_DOMAIN_ISSUE_ID_HPP
#define FIX_SRC_DOMAIN_ISSUE_ID_HPP

#include "description.hpp"
#include "title.hpp"

namespace fix::domain {

class issue_id {
  std::string text;

  explicit issue_id(std::string text);

public:
  //  move-only; rule of 5
  issue_id(issue_id const&) = delete;
  issue_id(issue_id&&) = default;
  issue_id& operator=(issue_id const&) = delete;
  issue_id& operator=(issue_id&&) = default;
  ~issue_id() = default;

  static issue_id generate(title const& title, description const& description);

  // cppcheck-suppress functionStatic
  std::string const& to_string() const;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_ISSUE_ID_HPP
