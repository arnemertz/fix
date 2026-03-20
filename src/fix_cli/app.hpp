#ifndef FIX_APP_HPP
#define FIX_APP_HPP

#include <iosfwd>

namespace fix::domain {
class issue_service;
}

namespace fix::cli {

class app {
  std::ostream& out;
  fix::domain::issue_service& service_;

public:
  app(std::ostream& out, fix::domain::issue_service& service);

  auto run(int argc, char const* const* argv) -> int;
};

} // namespace fix::cli

#endif // FIX_APP_HPP
