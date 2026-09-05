#pragma once

#include <filesystem>
#include <vector>

/// @brief Utility class for discovering files within local directory paths.
class Scanner {
public:
  /// @brief Scans a directory or validates a single file path for search
  /// operations.
  /// @param path Base directory path to scan, or a single file path.
  /// @param recursive Set to true to traverse subdirectories, or false to scan
  /// only top-level directory items.
  /// @return A vector of path objects corresponding to discovered files.
  static std::vector<std::filesystem::path>
  scan(const std::filesystem::path &path, bool recursive);
};
