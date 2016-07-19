#ifndef FIX_HTMLREQUESTHANDLER_H
#define FIX_HTMLREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"

namespace Fix {
  namespace Server {

    class HTMLRequestHandler : public Poco::Net::HTTPRequestHandler {
      void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
    };

  }
}

#endif //FIX_HTMLREQUESTHANDLER_H
