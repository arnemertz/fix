#ifndef FIX_TEST_DOMAIN_IN_MEMORY_ISSUE_REPOSITORY_HPP
#define FIX_TEST_DOMAIN_IN_MEMORY_ISSUE_REPOSITORY_HPP

#include <map>
#include <ranges>
#include <string>

#include "issue_repository.hpp"

namespace fix::test {

class in_memory_issue_repository : public domain::issue_repository {
  std::map<std::string, domain::issue> issues_;

  static domain::issue clone(domain::issue const& iss) {
    return domain::issue::create(iss.get_title().to_string(), iss.get_description().to_string()).value();
  }

public:
  domain::expected<void> save(domain::issue const& issue) override {
    auto id_str = issue.id().to_string();
    issues_.erase(id_str);
    issues_.emplace(std::move(id_str), clone(issue));
    return {};
  }

  domain::expected<std::vector<domain::issue>> find_all() const override {
    return issues_ | std::views::values | std::views::transform([](domain::issue const& iss) { return clone(iss); })
         | std::ranges::to<std::vector<domain::issue>>();
  }

  bool exists(domain::issue_id const& id) const override {
    return issues_.contains(id.to_string());
  }
};

} // namespace fix::test

#endif // FIX_TEST_DOMAIN_IN_MEMORY_ISSUE_REPOSITORY_HPP
