#ifndef FIX_TEST_DOMAIN_IN_MEMORY_ISSUE_REPOSITORY_HPP
#define FIX_TEST_DOMAIN_IN_MEMORY_ISSUE_REPOSITORY_HPP

#include "issue_repository.hpp"

#include <map>
#include <string>
#include <vector>

namespace fix::test {

class in_memory_issue_repository : public domain::issue_repository {
  std::map<std::string, domain::issue> issues_;

public:
  domain::expected<void> save(domain::issue const& issue) override {
    auto id_str = issue.id().to_string();
    auto copy = domain::issue::create(issue.get_title().to_string(),
                                      issue.get_description().to_string());
    if (!copy) {
      return std::unexpected(copy.error());
    }
    issues_.erase(id_str);
    issues_.emplace(std::move(id_str), std::move(*copy));
    return {};
  }

  domain::expected<std::vector<domain::issue>> find_all() const override {
    std::vector<domain::issue> result;
    for (auto const& [id, iss] : issues_) {
      auto issue_copy = domain::issue::create(iss.get_title().to_string(),
                                              iss.get_description().to_string());
      if (issue_copy) {
        result.push_back(std::move(*issue_copy));
      }
    }
    return result;
  }

  bool exists(domain::issue_id const& id) const override {
    return issues_.contains(id.to_string());
  }
};

} // namespace fix::test

#endif // FIX_TEST_DOMAIN_IN_MEMORY_ISSUE_REPOSITORY_HPP
