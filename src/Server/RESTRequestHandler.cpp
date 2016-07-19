#include "RESTRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

#include "json.hpp"
using Json = nlohmann::json;

using namespace Fix::Server;

void RESTRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
  response.setChunkedTransferEncoding(true);
  response.setContentType("application/json");

  std::ostream& ostr = response.send();
  ostr << Json {
    { "error", {
      { "message", "Unsupported operation." }
    }},
    { "links",  request.getURI() }
  };
}
