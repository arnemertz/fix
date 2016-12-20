#include "Issue.h"

using namespace fix;

IssueParseResult IssueData::parse(Json const& issueJson) {
  using namespace std::string_literals;
  if (issueJson.count("data") == 0) {
    return {{}, false};
  }
  if (issueJson["data"].count("ID") != 0) {
    return {{}, false};
  }
  for (auto const &attribute : {"summary"s, "description"s}) {
    if (issueJson["data"].count(attribute) == 0) {
      return {{}, false};
    }
  }
  return {IssueData{issueJson}, true};
}
