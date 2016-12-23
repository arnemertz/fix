#ifndef FIX_TEXTFILESTORAGE_H
#define FIX_TEXTFILESTORAGE_H

#include <Poco/Path.h>
#include "Storage.h"
#include "FileAccess.h"

namespace fix {
  namespace storage {

    class TextFileStorage : public Storage {
      static unsigned const STORED_JSON_INDENTATION = 2;
      FileAccess& fileAccess;
      Poco::Path const storageDirectoryPath;
      Poco::Path const issueDirectoryPath;
    public:

      TextFileStorage(FileAccess& fa);
      unsigned selectMaxIssueID() const override;
      Json insertIssueIncreasedID(const Json &requestedIssue) override;
      std::vector<Json> allIssues() const override;
      Json issue(unsigned id) const override;

    private:
      void insertIssue(Json);

      Json readIssue(const Poco::Path &path) const;

    };

  }
}

#endif //FIX_TEXTFILESTORAGE_H
