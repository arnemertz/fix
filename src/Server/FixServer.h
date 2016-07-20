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

  class RestApi;

  namespace Server {

    class FixServer : public Poco::Util::ServerApplication {
      RestApi& restApi;
    public:
      FixServer(RestApi& api);
    private:

      void initialize(Application &self) override;
      int main(const std::vector<std::string> &args) override;

      void createFixDirectory() const;
      void serve();
    };

  }
}

#endif //FIX_FIXSERVER_H
