#ifndef FIX_STORAGE_H
#define FIX_STORAGE_H

#include "Json.h"

namespace Fix {

  class Storage {
  public:
    virtual void insertIssue(Json) = 0;
  };
  
}

#endif //FIX_STORAGE_H
