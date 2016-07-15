#include "RequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

using namespace fix::Server;

HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(HTTPServerRequest const &request) {
  return nullptr;
}
