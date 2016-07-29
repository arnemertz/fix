#include "server/FixServer.h"
#include "RestApi.h"
#include "Storage.h"

class DummyStorage : public fix::Storage {
  void insertIssue(fix::Json) override {}
};

int main(int argc, char** argv) {
  DummyStorage storage;
  fix::RestApi api{storage};

  fix::server::FixServer server{api};
  return server.run(argc, argv);
}
