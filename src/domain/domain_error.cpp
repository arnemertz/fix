#include "domain_error.hpp"

namespace fix::domain {
namespace {

std::string error_message(fix::domain::domain_error error) {
  switch (error) {
  case domain_error::MISSING_IMPLEMENTATION:
    return "feature is not implemented yet";
  case domain_error::TITLE_TOO_LONG:
    return "title is too long";
  case domain_error::TITLE_TOO_SHORT:
    return "title is too short";
  }
  return "unknown domain error";
}

// =========================================================
// wiring to enable use of std::error_code with domain_error
// =========================================================

struct fix_error_category_t : std::error_category {
  [[nodiscard]] char const* name() const noexcept override {
    return "fix domain error";
  }

  [[nodiscard]] std::string message(int condition) const override {
    return error_message(static_cast<fix::domain::domain_error>(condition));
  };
};

const fix_error_category_t fix_error_category;
} // namespace

std::error_code make_error_code(domain_error error) {
  return {static_cast<int>(error), fix_error_category};
}

} // namespace fix::domain
