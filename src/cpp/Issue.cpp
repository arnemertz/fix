#include "Issue.h"

using namespace fix;

IssueParseResult IssueData::parse(Json const& issueJson) {
  using namespace std::string_literals;
  if (issueJson.count("data") == 0) {
    return {{}, false};
  }
  auto const& dataJson = issueJson["data"];
  if (dataJson.count("ID") != 0) {
    return {{}, false};
  }

  for (auto const &attribute : {"summary"s, "description"s}) {
    if (dataJson.count(attribute) == 0) {
      return {{}, false};
    }
  }

  IssueData issueData;
  issueData.summary = dataJson["summary"];
  issueData.description = dataJson["description"];
  return {issueData, true};
}
