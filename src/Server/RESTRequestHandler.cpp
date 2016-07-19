#include "RESTRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"

using namespace Fix::Server;

void RESTRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
  response.setChunkedTransferEncoding(true);
  response.setContentType("application/json");

  std::ostream& ostr = response.send();
  ostr << R"({ "location": ")" + request.getURI() + R"(" })";
}
