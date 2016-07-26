#include "TestFrameworks.h"

#include "Json.h"
#include "RestApi.h"
#include "Storage.h"
using namespace Fix;

class StorageMock : public Storage {
public:
  MAKE_MOCK1(insertIssue, void(Json), override);
};

TEST_CASE( "Creating an issue returns the issue with its data and an ID", "[issue]" ) {
  StorageMock storage;
  Fix::RestApi api{storage};

  std::string uri = "issue/new";
  std::string method = "POST";
  Json requestedIssue = {
      { "data", {
        { "summary", "New Issue" },
        { "description", "Some lengthy text here to describe the issue" }
      }}
  };

  Json expectedIssue = requestedIssue;
  expectedIssue["data"]["ID"] = 1;

  REQUIRE_CALL(storage, insertIssue(expectedIssue));

  Json response = api.process(uri, method, requestedIssue.dump());

  REQUIRE(response == expectedIssue);
}
