#include "RESTRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/StreamCopier.h"

#include "Json.h"
#include "RestApi.h"

using namespace fix::server;

RESTRequestHandler::RESTRequestHandler(RestApi &api)
  : restApi{api}
{}

void RESTRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
  auto uri = request.getURI();
  auto method = request.getMethod();

  std::string content;
  Poco::StreamCopier::copyToString(request.stream(), content);

  auto apiResponse = restApi.process(uri, method, content);

  response.setChunkedTransferEncoding(true);
  response.setContentType("application/json");

  std::ostream& ostr = response.send();
  ostr << apiResponse;
}
