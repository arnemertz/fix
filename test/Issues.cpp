#include "TestFrameworks.h"

#include "Json.h"
#include "RestApi.h"
#include "Storage.h"
using namespace fix;

class StorageMock : public Storage {
public:
  MAKE_MOCK1(insertIssue, void(Json), override);
};

TEST_CASE( "Creating an issue...", "[issue]" ) {
  StorageMock storage;
  fix::RestApi api{storage};

  std::string uri = "/issue/new";
  std::string method = "POST";
  auto requestedIssue = Json {
      { "data", {
        { "summary", "New Issue" },
        { "description", "Some lengthy text here to describe the issue" }
      }}
  };
  auto request = requestedIssue.dump();


  SECTION("... creates and returns the issue with its data and an ID if the input is correct.") {
    auto expectedIssue = requestedIssue;
    expectedIssue["data"]["ID"] = 1;

    REQUIRE_CALL(storage, insertIssue(expectedIssue));
    auto response = api.process(uri, method, request);
    REQUIRE(response == expectedIssue);
  }


  SECTION("... returns status 400 with corresponding error message if...") {
    using trompeloeil::_;
    auto status400 = Json {{ "status", 400 }};
    auto response = Json {};
    FORBID_CALL(storage, insertIssue(_));

    SECTION("... the method is wrong.") {
      status400["error"] = "expected POST method for " + uri;
      response = api.process(uri, "GET", request);
    }

    SECTION("... the request can not be parsed.") {
      status400["error"] = "error parsing request";
      response = api.process(uri, method, "{ some non-json string");
    }

    REQUIRE(response == status400);
  }
}
