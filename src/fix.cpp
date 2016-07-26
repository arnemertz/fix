#include "Server/FixServer.h"
#include "RestApi.h"
#include "Storage.h"

class DummyStorage : public Fix::Storage {
  void insertIssue(Fix::Json) override {}
};

int main(int argc, char** argv) {
  DummyStorage storage;
  Fix::RestApi api{storage};

  Fix::Server::FixServer server{api};
  return server.run(argc, argv);
}
