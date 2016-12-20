#ifndef FIX_RESTAPI_H
#define FIX_RESTAPI_H

#include <string>
#include "Json.h"
#include "Issue.h"

namespace fix {
  class Storage;

  class RestApi {
    Storage& storage;

  public:
    struct Response {
      Json content;
      int httpCode;
    };

    RestApi(Storage& st);
    Response process(std::string const& requestUri, std::string const& requestMethod, std::string const& requestContent) const;
  private:
    static RestApi::Response status400();

    bool parseIssue(const std::string &requestContent, IssueData &requestedIssue) const;
  };
}


#endif //FIX_RESTAPI_H
