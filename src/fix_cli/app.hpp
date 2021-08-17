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

private:
  int run_command(std::string const& command, const std::vector<std::string>& argv);
  int list();
  int create(std::vector<std::string> const& argv);
};

} // namespace fix::cli

#endif // FIX_APP_HPP
