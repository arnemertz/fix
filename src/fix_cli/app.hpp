#ifndef FIX_APP_HPP
#define FIX_APP_HPP

#include <iosfwd>
#include <string_view>
#include <vector>

namespace fix::cli {

class app {
public:
  explicit app(std::ostream &out);

  void run(std::vector<std::string_view> const &);
};

}

#endif //FIX_APP_HPP
