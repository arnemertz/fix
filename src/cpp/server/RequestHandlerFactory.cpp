#include "RequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "HTMLRequestHandler.h"
#include "RESTRequestHandler.h"

using namespace Poco::Net;
using namespace fix::server;

RequestHandlerFactory::RequestHandlerFactory(RestApi& api)
    : restApi{api}
{}

HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(HTTPServerRequest const &request) {
  if (request.getURI() == "/")
    return new HTMLRequestHandler;
  else
    return new RESTRequestHandler(restApi);
}
