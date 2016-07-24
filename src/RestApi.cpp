#include "RestApi.h"

using namespace Fix;

Json RestApi::process(std::string const &requestUri, std::string const &requestMethod, std::string const &requestContent) const {
  if (requestUri == "issue/new") {
    Json newIssue = Json::parse(requestContent);
    newIssue["data"]["ID"] = 1;
    return newIssue;
  }

  return {
      { "error", {
        { "message", "Unsupported operation." }
      }},
      { "links",  requestUri }
  };
}


