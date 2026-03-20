#include "toml_issue_repository.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <toml++/toml.h>

using namespace fix::infrastructure;
using namespace fix::domain;
namespace fs = std::filesystem;

toml_issue_repository::toml_issue_repository(std::filesystem::path fix_root)
    : issues_dir_{std::move(fix_root) / "issues"} {}

expected<void> toml_issue_repository::save(issue const& iss) {
  try {
    // Ensure directory exists
    if (!fs::exists(issues_dir_)) {
      fs::create_directories(issues_dir_);
    }

    // Build TOML structure
    toml::table tbl;
    tbl.insert_or_assign("title", iss.get_title().to_string());
    tbl.insert_or_assign("description", iss.get_description().to_string());

    // Write to file
    auto const filename = issues_dir_ / (iss.id().to_string() + ".toml");
    std::ofstream file(filename);
    if (!file) {
      return std::unexpected(std::make_error_code(std::errc::io_error));
    }
    file << tbl;
    return {};
  } catch (...) {
    return std::unexpected(std::make_error_code(std::errc::io_error));
  }
}

expected<std::vector<issue>> toml_issue_repository::find_all() const {
  std::vector<issue> issues;

  try {
    if (!fs::exists(issues_dir_)) {
      return issues; // Empty list if directory doesn't exist yet
    }

    for (auto const& entry : fs::directory_iterator(issues_dir_)) {
      if (entry.path().extension() != ".toml") {
        continue;
      }

      // Parse TOML file
      auto const tbl = toml::parse_file(entry.path().string());
      auto const title_str = tbl["title"].value<std::string>();
      auto const desc_str = tbl["description"].value<std::string>();

      if (!title_str || !desc_str) {
        continue; // Skip malformed files
      }

      // Create issue from stored data
      auto iss_result = issue::create(*title_str, *desc_str);
      if (iss_result) {
        issues.push_back(std::move(*iss_result));
      }
    }

    // Sort by ID (alphabetically)
    std::ranges::sort(issues, [](auto const& a, auto const& b) {
      return a.id().to_string() < b.id().to_string();
    });

    return issues;
  } catch (...) {
    return std::unexpected(std::make_error_code(std::errc::io_error));
  }
}

bool toml_issue_repository::exists(issue_id const& id) const {
  auto const filename = issues_dir_ / (id.to_string() + ".toml");
  return fs::exists(filename);
}
