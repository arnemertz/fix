#include "catch.hpp"

#include "RestApi.h"
#include "Json.h"
using namespace Fix;

TEST_CASE( "Creating an issue returns the issue with its data and an ID", "[issue]" ) {
  Fix::RestApi api;

  std::string uri = "issue/new";
  std::string method = "POST";
  Json issue = {
      { "data", {
        { "summary", "New Issue" },
        { "description", "Some lengthy text here to describe the issue" }
      }}
  };

  Json response = api.process(uri, method, issue.dump());

  Json requiredResponse = issue;
  requiredResponse["data"]["ID"] = 1;
  REQUIRE(response == requiredResponse);
}
