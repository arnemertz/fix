#include <iostream>

#include "fix_cli/app.hpp"

int main(int argc, char* argv[]) {
  fix::cli::app app{std::cout};
  return app.run(argc, argv);
}
