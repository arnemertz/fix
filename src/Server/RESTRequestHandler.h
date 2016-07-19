#ifndef FIX_RESTREQUESTHANDLER_H
#define FIX_RESTREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"

namespace Fix {
  namespace Server {

    class RESTRequestHandler : public Poco::Net::HTTPRequestHandler {
      void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
    };

  }
}

#endif //FIX_RESTREQUESTHANDLER_H
