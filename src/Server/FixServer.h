#ifndef FIX_FIXSERVER_H
#define FIX_FIXSERVER_H

#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"

#include "RequestHandlerFactory.h"

using Poco::Util::Application;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

namespace fix {
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
        HTTPServer srv{new Server::RequestHandlerFactory, svs, new HTTPServerParams};
        srv.start();
        waitForTerminationRequest();
        srv.stop();

        return Application::EXIT_OK;
      }
    };

  }
}

#endif //FIX_FIXSERVER_H
