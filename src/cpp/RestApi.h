#ifndef FIX_RESTAPI_H
#define FIX_RESTAPI_H

#include <string>
#include "Json.h"

namespace fix {
  class Storage;
  class IssueParseResult;

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

    Response issue_new(const std::string &requestContent) const;
    Response issue_list() const;
    Response issue_id(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &id_string) const;
  };
}

#endif //FIX_RESTAPI_H
