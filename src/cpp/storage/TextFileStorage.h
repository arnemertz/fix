#ifndef FIX_TEXTFILESTORAGE_H
#define FIX_TEXTFILESTORAGE_H

#include "Storage.h"
#include <Poco/Path.h>

namespace fix {
  namespace storage {

    class TextFileStorage : public Storage {
      static unsigned const STORED_JSON_INDENTATION = 2;
      Poco::Path const storageDirectoryPath;
      Poco::Path const issueDirectoryPath;
    public:

      TextFileStorage();
      void insertIssue(Json) override;
      unsigned selectMaxIssueID() const override;
    };

  }
}



#endif //FIX_TEXTFILESTORAGE_H
