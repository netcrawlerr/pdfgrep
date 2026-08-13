#include "../include/scanner.h"

#include <algorithm>
#include <cctype>

namespace {

bool isPdf(const std::filesystem::path &path) {
  if (!path.has_extension()) {
    return false;
  }

  std::string extension = path.extension().string();

  std::transform(
      extension.begin(), extension.end(), extension.begin(),
      [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

  return extension == ".pdf";
}

} // namespace

std::vector<std::filesystem::path>
Scanner::scan(const std::filesystem::path &path, bool recursive) {
  std::vector<std::filesystem::path> files;

  if (!std::filesystem::exists(path)) {
    return files;
  }

  if (std::filesystem::is_regular_file(path)) {
    if (isPdf(path)) {
      files.push_back(path);
    }

    return files;
  }

  if (!std::filesystem::is_directory(path)) {
    return files;
  }

  try {
    if (recursive) {
      for (const auto &entry :
           std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file() && isPdf(entry.path())) {
          files.push_back(entry.path());
        }
      }
    } else {
      for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && isPdf(entry.path())) {
          files.push_back(entry.path());
        }
      }
    }
  } catch (const std::filesystem::filesystem_error &) {
    return files;
  }

  std::sort(files.begin(), files.end());

  return files;
}
