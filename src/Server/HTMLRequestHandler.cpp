#include "HTMLRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Fix::Server;

void HTMLRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
  response.setChunkedTransferEncoding(true);
  response.setContentType("text/html");

  std::ostream& ostr = response.send();
  ostr << "<html><head><title>Fix</title><meta></head><body>";
  ostr << "<p style=\"text-align: center; font-size: 48px;\">Fix!</p><hr>";
  ostr << "</body></html>";
}
