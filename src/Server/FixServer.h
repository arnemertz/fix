#ifndef FIX_FIXSERVER_H
#define FIX_FIXSERVER_H

#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"

#include "RequestHandlerFactory.h"

using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

namespace Fix {
  namespace Server {

    class FixServer : public Poco::Util::ServerApplication {
      void initialize(Application &self) override {
        loadConfiguration();
        ServerApplication::initialize(self);
      }

      int main(const std::vector<std::string> &args) override {
        using namespace Poco::Net;
        Poco::UInt16 port = config().getInt("FixServer.port", 8080);

        ServerSocket svs{port};
        HTTPServer srv{new RequestHandlerFactory, svs, new HTTPServerParams};
        srv.start();
        logger().information("Server started.");
        waitForTerminationRequest();
        srv.stop();
        logger().information("Server stopped.");

        return Application::EXIT_OK;
      }
    };

  }
}

#endif //FIX_FIXSERVER_H
