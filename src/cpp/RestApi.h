#ifndef FIX_RESTAPI_H
#define FIX_RESTAPI_H

#include <string>
#include "Json.h"

namespace fix {
  class Storage;

  class RestApi {
    Storage& storage;
  public:
    RestApi(Storage& st);
    Json process(std::string const& requestUri, std::string const& requestMethod, std::string const& requestContent) const;
  private:
    static Json status400(std::string const &message);

    Json insertIssueIncreasedID(const Json &requestedIssue) const;
  };

}

#endif //FIX_RESTAPI_H
