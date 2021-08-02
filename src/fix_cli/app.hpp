#ifndef FIX_APP_HPP
#define FIX_APP_HPP

#include <iosfwd>
#include <string_view>
#include <vector>

namespace fix::cli {

class app {
  std::ostream& out;

public:
  explicit app(std::ostream& out);

  auto run(std::vector<std::string_view> const& args) -> int;
};

} // namespace fix::cli

#endif // FIX_APP_HPP
