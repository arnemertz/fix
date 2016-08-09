#ifndef FIX_RESTREQUESTHANDLER_H
#define FIX_RESTREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"

namespace fix {

  class RestApi;

  namespace server {

    class RESTRequestHandler : public Poco::Net::HTTPRequestHandler {
      RestApi& restApi;
    public:
      RESTRequestHandler(RestApi& api);
      void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
    };

  }
}

#endif //FIX_RESTREQUESTHANDLER_H
