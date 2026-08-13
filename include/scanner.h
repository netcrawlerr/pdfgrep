#pragma once

#include <filesystem>
#include <vector>

class Scanner {
public:
  static std::vector<std::filesystem::path>
  scan(const std::filesystem::path &path, bool recursive);
};
