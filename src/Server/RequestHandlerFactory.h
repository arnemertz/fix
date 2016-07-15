#ifndef FIX_FIXREQUESTHANDLERFACTORY_H
#define FIX_FIXREQUESTHANDLERFACTORY_H

#include "Poco/Net/HTTPRequestHandlerFactory.h"

namespace fix {
  namespace Server {

    class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
      Poco::Net::HTTPRequestHandler* createRequestHandler(Poco::Net::HTTPServerRequest const &request) override;
    };

  }
}

#endif //FIX_FIXREQUESTHANDLERFACTORY_H
