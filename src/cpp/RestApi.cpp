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
  if (requestUri == "/issue/new") {
    if (requestMethod != "POST") {
      return Response::badRequest();
    }
    return issue_new(requestContent);
  } else if (requestUri == "/issue/list") {
    if (requestMethod != "GET") {
      return Response::methodNotAllowed();
    }
    return issue_list();
  } else {
    std::regex issue_id_regex{"/issue/([0-9]*)"};
    std::smatch id_match;
    if (std::regex_match(requestUri, id_match, issue_id_regex)) {
      auto id_string = id_match[1].str();
      return issue_id(id_string);
    }
  }

  return Response::methodNotAllowed();
}

RestApi::Response RestApi::issue_id(std::string const& id_string) const {
  Json issue = storage.issue(stoul(id_string));
  if (!issue.empty()) {
    return Response::ok(issue);
  }
  return Response::notFound();
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

