#ifndef FIX_APP_HPP
#define FIX_APP_HPP

#include <iosfwd>
#include <string>

namespace fix::domain { class issue_service; }

namespace fix::cli {

class app {
  std::ostream& out;
  fix::domain::issue_service& service_;

public:
  app(std::ostream& out, fix::domain::issue_service& service);

  auto run(int argc, char const* const* argv) -> int;

private:
  int list();
  int create(std::string const& title, std::string const& description);
};

} // namespace fix::cli

#endif // FIX_APP_HPP
