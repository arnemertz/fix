#ifndef FIX_ISSUE_H
#define FIX_ISSUE_H

#include "Json.h"

namespace fix {
  class IssueParseResult;

  class IssueData {
    std::string summary;
    std::string description;
  public:
    Json toStorageJson() const {
      return Json{
        {"data", {
          {"summary", summary},
          {"description", description}
        }}
      };
    }

    static IssueParseResult parse(Json const& issueJson);
  };

  struct IssueParseResult {
    IssueData issueData;
    bool success;
  };
}


#endif //FIX_ISSUE_H
