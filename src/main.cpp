#include <iostream>

#include "fix_cli/app.hpp"

int main(int argc, char* argv[]) {
  fix::cli::app app{std::cout};
  const std::vector<std::string_view> args(std::next(argv), std::next(argv, argc));
  return app.run(args);
}
