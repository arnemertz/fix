#include "application_service.hpp"

#include <range/v3/view.hpp>
#include <range/v3/range/conversion.hpp>
#include <string>

using namespace fix::domain;
using namespace std::literals;
namespace rv = ranges::views;

std::string application_service::create(std::string_view title, std::string_view description) { // NOLINT
  (void) description;

  // clang-format off
  const auto id_prefix = title
      | rv::split(' ')
      | rv::take(4)
      | rv::transform([](auto&& word) {
        return word | rv::take(3) | rv::transform([](char c){ return std::tolower(c); });
      })
      | rv::join('-')
      | ranges::to<std::string>;
  // clang-format on

  return id_prefix + "-0000000"s;
}
