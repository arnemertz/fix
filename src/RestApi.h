#ifndef FIX_RESTAPI_H
#define FIX_RESTAPI_H

#include <string>
#include "Json.h"

namespace Fix {

  class RestApi {
  public:
    Json process(std::string const &requestUri, std::string const &requestMethod, std::string const &requestContent) const;
  };

}

#endif //FIX_RESTAPI_H
