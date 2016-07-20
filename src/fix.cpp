#include "Server/FixServer.h"
#include "RestApi.h"

int main(int argc, char** argv) {
  Fix::RestApi api;

  Fix::Server::FixServer server{api};
  return server.run(argc, argv);
}
