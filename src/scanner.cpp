#include "../include/scanner.h"

#include <algorithm>
#include <cctype>

namespace {

// Internal helper: Inspects the file extension in a case-insensitive manner.
bool isPdf(const std::filesystem::path &path) {
  if (!path.has_extension()) {
    return false;
  }

  std::string extension = path.extension().string();

  // Normalize path extension to lowercase to catch both .pdf and .PDF.
  std::transform(
      extension.begin(), extension.end(), extension.begin(),
      [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

  return extension == ".pdf";
}

} // namespace

std::vector<std::filesystem::path>
Scanner::scan(const std::filesystem::path &path, bool recursive) {
  std::vector<std::filesystem::path> files;

  // Verify path existence on the filesystem before proceeding.
  if (!std::filesystem::exists(path)) {
    return files;
  }

  // Direct target case: path points directly to a single regular file.
  if (std::filesystem::is_regular_file(path)) {
    if (isPdf(path)) {
      files.push_back(path);
    }

    return files;
  }

  // Guard clause against non-directory special files (sockets, devices,
  // symlinks to nothing, etc.).
  if (!std::filesystem::is_directory(path)) {
    return files;
  }

  // Catch permission denied or directory access exceptions during iteration.
  try {
    if (recursive) {
      // Traverse directory tree recursively using std::filesystem iterator.
      for (const auto &entry :
           std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file() && isPdf(entry.path())) {
          files.push_back(entry.path());
        }
      }
    } else {
      // Perform top-level directory traversal only.
      for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && isPdf(entry.path())) {
          files.push_back(entry.path());
        }
      }
    }
  } catch (const std::filesystem::filesystem_error &) {
    return files;
  }

  // Sort discovered file paths lexicographically for consistent output
  // ordering.
  std::sort(files.begin(), files.end());

  return files;
}
