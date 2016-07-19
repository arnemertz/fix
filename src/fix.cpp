#include "Server/FixServer.h"

int main(int argc, char** argv) {
  Fix::Server::FixServer server;
  return server.run(argc, argv);
}
