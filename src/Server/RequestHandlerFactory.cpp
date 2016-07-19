#include "RequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "HTMLRequestHandler.h"

using namespace Poco::Net;

using namespace Fix::Server;

HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(HTTPServerRequest const &request) {
  if (request.getURI() == "/")
    return new HTMLRequestHandler;
  else
    return nullptr;
}
