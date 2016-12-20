#ifndef FIX_ISSUE_H
#define FIX_ISSUE_H

#include "Json.h"

namespace fix {
  class IssueData {
    Json content;
  public:
    IssueData(Json requestJson) : content{std::move(requestJson)} {}
    IssueData() = default;
    Json toStorageJson() const {
      return content;
    }
  };

  struct IssueParseResult {
    IssueData issueData;
    bool success;
  };
}


#endif //FIX_ISSUE_H
