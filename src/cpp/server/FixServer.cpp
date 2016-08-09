#include "FixServer.h"

using namespace fix::server;

FixServer::FixServer(RestApi& api)
    : restApi{api}
{}

int FixServer::main(const std::vector<std::string> &args) {
  serve();
  return Application::EXIT_OK;
}

void FixServer::serve() {
  using namespace Poco::Net;
  Poco::UInt16 port = config().getInt("FixServer.port", 8080);
  ServerSocket svs{port};
  HTTPServer srv{new RequestHandlerFactory(restApi), svs, new HTTPServerParams};
  srv.start();
  logger().information("Server started.");
  waitForTerminationRequest();
  srv.stop();
  logger().information("Server stopped.");
}

void FixServer::initialize(Application &self) {
  loadConfiguration();
  ServerApplication::initialize(self);
}
