#include "server/FixServer.h"
#include "RestApi.h"
#include "storage/TextFileStorage.h"

int main(int argc, char** argv) {
  using namespace fix;
  storage::TextFileStorage storage;
  RestApi api{storage};

  server::FixServer server{api};
  return server.run(argc, argv);
}
