#ifndef FIX_TEXTFILESTORAGE_H
#define FIX_TEXTFILESTORAGE_H

#include <Poco/Path.h>
#include "Storage.h"

namespace fix {
  namespace storage {

    class TextFileStorage : public Storage {
      static unsigned const STORED_JSON_INDENTATION = 2;
      Poco::Path const storageDirectoryPath;
      Poco::Path const issueDirectoryPath;
    public:

      TextFileStorage();
      unsigned selectMaxIssueID() const override;
      Json insertIssueIncreasedID(const Json &requestedIssue) override;
      std::vector<Json> allIssues() const override;

    private:
      void insertIssue(Json);
    };

  }
}

#endif //FIX_TEXTFILESTORAGE_H
