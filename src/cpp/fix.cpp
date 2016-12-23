#include "server/FixServer.h"
#include "RestApi.h"
#include "storage/TextFileStorage.h"
#include "storage/FileAccess.h"

int main(int argc, char** argv) {
  using namespace fix;
  storage::FileAccess fileAccess;
  storage::TextFileStorage storage{fileAccess};
  RestApi api{storage};

  server::FixServer server{api};
  return server.run(argc, argv);
}
