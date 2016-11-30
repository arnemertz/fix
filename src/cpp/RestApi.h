#ifndef FIX_RESTAPI_H
#define FIX_RESTAPI_H

#include <string>
#include "Json.h"

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
    static Response status400(std::string const &message);
  };
}


#endif //FIX_RESTAPI_H
