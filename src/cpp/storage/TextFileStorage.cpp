#include <fstream>
#include <Poco/File.h>
#include <Poco/DirectoryIterator.h>
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

TextFileStorage::TextFileStorage(FileAccess& fa)
  : fileAccess{fa}
  , storageDirectoryPath{getStorageDirectoryPath()}
  , issueDirectoryPath{storageDirectoryPath, "issues"}
{
  fileAccess.createDirectory(storageDirectoryPath);
  fileAccess.createDirectory(issueDirectoryPath);
}

unsigned TextFileStorage::selectMaxIssueID() const {
  auto maxID = 0u;
  for (auto const& path : fileAccess.listFilesInDirectory(issueDirectoryPath)) {
    if (path.getExtension() != "json") {
      continue;
    }
    auto baseName = path.getBaseName();
    maxID = std::max(maxID, static_cast<unsigned>(std::stoul(baseName)));
  }
  return maxID;
}

Json TextFileStorage::insertIssueIncreasedID(Json const &requestedIssue) {
  auto newIssue = requestedIssue;
  newIssue["data"]["ID"] = selectMaxIssueID() + 1;
  insertIssue(newIssue);
  return newIssue;
}

void TextFileStorage::insertIssue(Json issue) {
  auto issueID = issue["data"]["ID"].dump();
  Path issuePath{issueDirectoryPath, issueID + ".json"};

  fileAccess.createFile(issuePath);
  std::string const& textToStore = issue.dump(STORED_JSON_INDENTATION) + '\n';
  fileAccess.writeToFile(issuePath, textToStore);
}

std::vector<Json> TextFileStorage::allIssues() const{
  std::vector<Json> issues;
  for (auto const& path : fileAccess.listFilesInDirectory(issueDirectoryPath)) {
    if (path.getExtension() != "json") {
      continue;
    }
    issues.push_back(readIssue(path));
  }
  return issues;
}

Json TextFileStorage::issue(unsigned id) const {
  Path issuePath{issueDirectoryPath, std::to_string(id) + ".json"};
  if (!fileAccess.fileExists(issuePath)) {
    return Json{};
  }
  return readIssue(issuePath);
}

Json TextFileStorage::readIssue(const Path &path) const {
  const std::string& content = fileAccess.dumpFile(path);
  return Json::parse(content);
}

