#pragma once

#include "pdf.h"

#include <string>
#include <vector>

struct SearchOptions {
  bool caseInsensitive = false;
  int context = 0;
};

struct SearchMatch {
  int page;
  std::string line;
  std::vector<std::string> contextBefore;
  std::vector<std::string> contextAfter;
};

class Search {
public:
  static std::vector<SearchMatch> search(const Pdf &pdf,
                                         const std::string &pattern,
                                         const SearchOptions &options);

private:
  static bool contains(const std::string &text, const std::string &pattern,
                       bool caseInsensitive);

  static std::string lower(const std::string &text);
};
