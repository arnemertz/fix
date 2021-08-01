#include <iostream>

#include "fix_cli/app.hpp"

int main(int argc, char* argv[]) {
  fix::cli::app app{std::cout};
  const std::vector<std::string_view> args(argv, std::next(argv, argc));
  app.run(args);
}
