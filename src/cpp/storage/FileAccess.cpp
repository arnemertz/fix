#include "TextFileStorage.h"
#include <fstream>
#include "FileAccess.h"

#include <Poco/DirectoryIterator.h>
#include <Poco/File.h>

using namespace fix::storage;

void FileAccess::createDirectory(const Poco::Path& path) const {
  Poco::File storageDir{path};
  storageDir.createDirectory();
}

std::vector<Poco::Path> FileAccess::listFilesInDirectory(Poco::Path const& path) const {
  std::vector<Poco::Path> files;
  for (Poco::DirectoryIterator it{path}, end{}; it != end; ++it) {
    auto element = it.path();
    Poco::File file{element};
    if (!file.isFile()) {
      continue;
    }
    files.push_back(element);
  }
  return files;
}

void FileAccess::createFile(Poco::Path const& issuePath) const {
  Poco::File issueFile{issuePath};
  issueFile.createFile();
}

void FileAccess::writeToFile(Poco::Path const& path, std::string const& textToStore) const {
  std::ofstream issueStream{path.toString()};
  issueStream << textToStore;
}

bool FileAccess::fileExists(const Poco::Path& path) const {
  return Poco::File{path}.exists();
}

std::string FileAccess::dumpFile(const Poco::Path& path) const {
  std::ifstream issueStream{path.toString()};
  std::string const& content{
      std::istreambuf_iterator<char>{issueStream},
      std::istreambuf_iterator<char>{}
  };
  return content;
}