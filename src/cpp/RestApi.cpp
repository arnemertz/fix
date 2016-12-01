#include "RestApi.h"
#include "Storage.h"

using namespace fix;
using namespace std::string_literals;

RestApi::RestApi(Storage &st)
  : storage{st} {
}

RestApi::Response RestApi::process(std::string const& requestUri, std::string const& requestMethod, std::string const& requestContent) const {
  if (requestUri == "/issue/new") {
    if (requestMethod != "POST") {
      return status400("expected POST method for " + requestUri);
    }

    try {
      auto requestedIssue = Json::parse(requestContent);
      if (requestedIssue.count("data") == 0) {
        return status400("request contains no data");
      }
      if (requestedIssue["data"].count("ID") != 0) {
        return status400("can not create issue with predefined ID");
      }
      for (auto const& attribute : {"summary"s, "description"s}) {
        if (requestedIssue["data"].count(attribute) == 0) {
          return status400("issue is missing required attribute " + attribute);
        }
      }
      return {storage.insertIssueIncreasedID(requestedIssue), 200};
    } catch(std::invalid_argument &) {
      return status400("error parsing request");
    }
  } else if (requestUri == "/issue/list") {
    if (requestMethod != "GET") {
      return {
          Json{}, 405
      };
    }

    Json response = Json::object();
    response["data"]["issues"] = Json::array();

    return {
      response, 200
    };
  }

  return {
      Json{}, 405
  };
}

RestApi::Response RestApi::status400(std::string const &message) {
  return {
      Json{
          {"status", 400},
          {"error",  message}
      },
      400
  };
}

