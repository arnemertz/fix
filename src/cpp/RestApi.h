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

      static Response ok(Json response) { return {response, 200}; }
      static Response badRequest() { return status(400); }
      static Response notFound() { return status(404); }
      static Response methodNotAllowed() { return status(405); }
    private:
      static Response status(int st) { return {Json{}, st};}
    };

    RestApi(Storage& st);
    Response process(std::string const& requestUri, std::string const& requestMethod, std::string const& requestContent) const;
  private:

    Response issue_new(const std::string &requestContent) const;
    Response issue_list() const;
    Response issue_id(const std::basic_string<char, std::char_traits<char>, std::allocator<char>> &id_string) const;
  };
}

#endif //FIX_RESTAPI_H
