#include <Poco/File.h>
#include <Poco/DirectoryIterator.h>
#include <fstream>
#include "TextFileStorage.h"

using namespace fix::storage;
using fix::Json;
using Poco::Path;
using Poco::File;

namespace {
  Path getStorageDirectoryPath() {
    Path storageDirPath{Path::current()};
    storageDirPath.pushDirectory(".fix");
    return storageDirPath.absolute();
  }
}

TextFileStorage::TextFileStorage()
  : storageDirectoryPath{getStorageDirectoryPath()}
  , issueDirectoryPath{storageDirectoryPath, "issues"}
{
  File storageDir{storageDirectoryPath};
  storageDir.createDirectory();
  File issueDir{issueDirectoryPath};
  issueDir.createDirectory();
}

void TextFileStorage::insertIssue(Json issue) {
  auto issueID = issue["data"]["ID"].dump();
  Path issuePath{issueDirectoryPath, issueID + ".json"};
  File issueFile{issuePath};
  issueFile.createFile();

  std::ofstream issueStream{issuePath.toString()};
  issueStream << issue.dump(STORED_JSON_INDENTATION) << std::endl;
}

unsigned TextFileStorage::selectMaxIssueID() const {
  auto maxID = 0u;
  for (Poco::DirectoryIterator it{issueDirectoryPath}, end{}; it != end; ++it) {
    auto path = it.path();
    if (path.getExtension() != "json") {
      continue;
    }
    auto baseName = path.getBaseName();
    maxID = std::max(maxID, static_cast<unsigned>(std::stoul(baseName)));

  }
  return maxID;
}

