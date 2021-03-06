#ifndef FIX_STORAGE_H
#define FIX_STORAGE_H

#include "Json.h"

namespace fix {

  class Storage {
  public:
    virtual unsigned selectMaxIssueID() const = 0;
    virtual Json insertIssueIncreasedID(const Json &requestedIssue) = 0;
    virtual std::vector<Json> allIssues() const = 0;
    virtual Json issue(unsigned id) const = 0;
  };
  
}

#endif //FIX_STORAGE_H
