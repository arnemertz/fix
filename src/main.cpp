#include <iostream>

#include "application_service.hpp"
#include "fix_cli/app.hpp"
#include "toml_issue_repository.hpp"

int main(int argc, char* argv[]) {
  fix::infrastructure::toml_issue_repository repository{".fix"};
  fix::domain::application_service service{repository};
  fix::cli::app app{std::cout, service};
  return app.run(argc, argv);
}
