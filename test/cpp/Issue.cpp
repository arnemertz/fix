#include "TestFrameworks.h"
#include "Issue.h"

using namespace fix;
using namespace std::string_literals;

TEST_CASE( "Parsing issue data...", "[issue][parsing]" ) {

  Json issueJson{
      {
          "data", {
                      {"summary", "Some issue"},
                      {"description", "Some text that describes the issue"}
                  }
      }
  };

  SECTION("... with correct input succeeds and results in IssueData that, converted back, result in the same JSON") {
    auto parseResult = IssueData::parse(issueJson);
    REQUIRE(parseResult.success == true);
    CHECK(parseResult.issueData.toStorageJson() == issueJson);
  }

  SECTION("... fails, when...") {
    SECTION("... the input contains not data") {
      issueJson = Json{};
    }

    SECTION("... the input contains an ID") {
      issueJson["data"]["ID"] = 44;
    }

    for (auto const& name : {"summary"s, "description"s}) {
      SECTION("... the input does not contain the "s + name + " attribute"s) {
        issueJson["data"].erase(name);
      }
    }

    auto parseResult = IssueData::parse(issueJson);
    CHECK(parseResult.success == false);
  }
}