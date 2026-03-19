#ifndef FIX_SRC_INFRASTRUCTURE_TOML_ISSUE_REPOSITORY_HPP
#define FIX_SRC_INFRASTRUCTURE_TOML_ISSUE_REPOSITORY_HPP

#include "issue_repository.hpp"

#include <filesystem>

namespace fix::infrastructure {

class toml_issue_repository : public domain::issue_repository {
  std::filesystem::path issues_dir_;

public:
  explicit toml_issue_repository(std::filesystem::path fix_root);

  domain::expected<void> save(domain::issue const& issue) override;
  domain::expected<std::vector<domain::issue>> find_all() const override;
  bool exists(domain::issue_id const& id) const override;
};

} // namespace fix::infrastructure

#endif // FIX_SRC_INFRASTRUCTURE_TOML_ISSUE_REPOSITORY_HPP
