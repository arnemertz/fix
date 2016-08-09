#ifndef FIX_TESTFRAMEWORKS_H
#define FIX_TESTFRAMEWORKS_H

#include "catch.hpp"
#include "trompeloeil.hpp"

namespace trompeloeil
{
  template <>
  struct reporter<trompeloeil::specialized>
  {
    static void send(trompeloeil::severity s,
                     const char* file,
                     unsigned long line,
                     const char* msg)
    {
      std::ostringstream os;
      if (line) os << file << ':' << line << '\n';
      os << msg;
      if (s == ::trompeloeil::severity::fatal)
      {
        FAIL(os.str());
      }
      CHECK(os.str() == "");
    }
  };
}

#endif //FIX_TESTFRAMEWORKS_H
