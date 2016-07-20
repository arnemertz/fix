#include "RestApi.h"

using namespace Fix;

Json RestApi::process(std::string const &requestUri, std::string const &requestMethod, std::string const &requestContent) const {
  return {
      { "error", {
        { "message", "Unsupported operation." }
      }},
      { "links",  requestUri }
  };
}


