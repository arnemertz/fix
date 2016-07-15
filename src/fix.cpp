#include "Server/FixServer.h"

int main(int argc, char** argv) {
  fix::Server::FixServer server;
  return server.run(argc, argv);
}
