#include "app.hpp"

#include <ostream>

using namespace fix::cli;
using namespace std::string_view_literals;

namespace {
constexpr auto USAGE = R"(usage: fix [--help] <command> [<args>]

Available commands:
   create        Create a new issue
   setstatus     Set the status of an issue
   list          List all existing issues
   show          Show a specific issue
)"sv;
}

app::app(std::ostream &out)
{
  out << USAGE;
}

void app::run(const std::vector<std::string_view>& /*args*/) { //NOLINT
}
