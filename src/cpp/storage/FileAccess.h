#ifndef FIX_FILEACCESS_H
#define FIX_FILEACCESS_H

#include "Storage.h"
#include <Poco/Path.h>

namespace fix {
  namespace storage {
    class FileAccess {

    public:
      void createDirectory(const Poco::Path& path) const;
      void createFile(const Poco::Path& issuePath) const;
      std::vector<Poco::Path> listFilesInDirectory(Poco::Path const& path) const;
      void writeToFile(const Poco::Path& path, const std::string& textToStore) const;
      bool fileExists(const Poco::Path& path) const;

      std::string dumpFile(const Poco::Path& path) const;
    };
  }
}


#endif //FIX_FILEACCESS_H
