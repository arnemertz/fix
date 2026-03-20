#ifndef FIX_SRC_DOMAIN_ISSUE_REPOSITORY_HPP
#define FIX_SRC_DOMAIN_ISSUE_REPOSITORY_HPP

#include <vector>

#include "domain_error.hpp"
#include "issue.hpp"
#include "issue_id.hpp"

namespace fix::domain {

class issue_repository {
public:
  virtual ~issue_repository() = default;

  virtual expected<void> save(issue const& issue) = 0;
  virtual expected<std::vector<issue>> find_all() const = 0;
  virtual bool exists(issue_id const& id) const = 0;
};

} // namespace fix::domain

#endif // FIX_SRC_DOMAIN_ISSUE_REPOSITORY_HPP
