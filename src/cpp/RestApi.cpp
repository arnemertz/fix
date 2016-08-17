#include "RestApi.h"
#include "Storage.h"

using namespace fix;

RestApi::RestApi(Storage &st)
  : storage{st} {
}

Json RestApi::process(std::string const &requestUri, std::string const &requestMethod, std::string const &requestContent) const {
  if (requestUri == "/issue/new") {
    if (requestMethod != "POST") {
      return status400("expected POST method for " + requestUri);
    }

    try {
      auto requestedIssue = Json::parse(requestContent);
      return storage.insertIssueIncreasedID(requestedIssue);
    } catch(std::invalid_argument&) {
      return status400("error parsing request");
    }
  }

  return {
      { "error", {
        { "message", "Unsupported operation." }
      }},
      { "links",  requestUri }
  };
}

Json RestApi::status400(std::string const &message) {
  return Json{
      {"status", 400},
      {"error", message}
  };
}

