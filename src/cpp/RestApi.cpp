#include "RestApi.h"
#include <regex>
#include "Storage.h"
#include "Issue.h"

using namespace fix;

RestApi::RestApi(Storage& st)
  : storage{st} {
}

RestApi::Response RestApi::process(std::string const& requestUri, std::string const& requestMethod,
                                   std::string const& requestContent) const {

  using ResourceFunction = std::function<Response(std::string const&, std::smatch const&)>;

  {
    std::string uriPattern = "/issue/new";
    std::string allowedMethod = "POST";
    ResourceFunction impl = [this](std::string const& requestContent, std::smatch const& id_match) {
      return issue_new(requestContent);
    };

    std::regex uriRegex{uriPattern};
    std::smatch uriMatch;
    if (std::regex_match(requestUri, uriMatch, uriRegex)) {
      if (requestMethod != allowedMethod) {
        return Response::methodNotAllowed();
      }
      return impl(requestContent, uriMatch);
    }
  }

  {
    std::string uriPattern = "/issue/list";
    std::string allowedMethod = "GET";
    ResourceFunction impl = [this](std::string const& requestContent, std::smatch const& id_match) {
      return issue_list();
    };

    std::regex uriRegex{uriPattern};
    std::smatch uriMatch;
    if (std::regex_match(requestUri, uriMatch, uriRegex)) {
      if (requestMethod != allowedMethod) {
        return Response::methodNotAllowed();
      }
      return impl(requestContent, uriMatch);
    }
  }

  {
    std::string uriPattern = "/issue/([0-9]*)";
    std::string allowedMethod = "GET";
    ResourceFunction impl = [this](std::string const& requestContent, std::smatch const& id_match) {
      auto id_string = id_match[1].str();
      return issue_id(id_string);
    };

    std::regex uriRegex{uriPattern};
    std::smatch uriMatch;
    if (std::regex_match(requestUri, uriMatch, uriRegex)) {
      if (requestMethod != allowedMethod) {
        return Response::methodNotAllowed();
      }
      return impl(requestContent, uriMatch);
    }
  }

  return Response::notFound();
}

RestApi::Response RestApi::issue_id(std::string const& id_string) const {
  Json issue = storage.issue(stoul(id_string));
  if (issue.empty()) {
    return Response::notFound();
  }
  return Response::ok(issue);
}

RestApi::Response RestApi::issue_list() const {
  Json data{
      {"issues", Json::array()}
  };
  auto all_issues = storage.allIssues();
  for (Json issue : all_issues) {
    issue["data"].erase("description");
    data["issues"].push_back(std::move(issue["data"]));
  }
  return Response::ok(Json{{"data", data}});
}

RestApi::Response RestApi::issue_new(std::string const& requestContent) const {
  try {
    auto issueJson = Json::parse(requestContent);
    auto parsedIssue = IssueData::parse(issueJson);
    if (!parsedIssue.success) {
      return Response::badRequest();
    }

    auto requestedIssue = parsedIssue.issueData;
    return {storage.insertIssueIncreasedID(requestedIssue.toStorageJson()), 200};
  } catch (std::invalid_argument&) {
    return Response::badRequest();
  }
}

