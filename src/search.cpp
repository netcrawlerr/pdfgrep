#include "../include/search.h"
#include <algorithm>
#include <sstream>

std::vector<SearchMatch> Search::search(const Pdf &pdf,
                                        const std::string &pattern,
                                        const SearchOptions &options) {
  std::vector<SearchMatch> matches;

  // Process document line-by-line across all extracted pages.
  for (const auto &page : pdf.pages()) {
    std::vector<std::string> lines;

    // Split page text block into individual line strings.
    std::stringstream stream(page.text);
    std::string line;

    while (std::getline(stream, line)) {
      lines.push_back(line);
    }

    // Evaluate each line against the target pattern.
    for (std::size_t i = 0; i < lines.size(); ++i) {
      if (!contains(lines[i], pattern, options.caseInsensitive)) {
        continue;
      }

      SearchMatch match;

      match.page = page.number;
      match.line = lines[i];

      const int context = options.context;

      // Bound context calculation within valid line index limits [0,
      // lines.size() - 1].
      const int start = std::max(0, static_cast<int>(i) - context);

      const int end = std::min(static_cast<int>(lines.size()) - 1,
                               static_cast<int>(i) + context);

      // Collect preceding context lines leading up to the current line index.
      for (int j = start; j < static_cast<int>(i); ++j) {
        match.contextBefore.push_back(lines[j]);
      }

      // Collect succeeding context lines following the current line index.
      for (int j = static_cast<int>(i) + 1; j <= end; ++j) {
        match.contextAfter.push_back(lines[j]);
      }

      matches.push_back(std::move(match));
    }
  }

  return matches;
}

bool Search::contains(const std::string &text, const std::string &pattern,
                      bool caseInsensitive) {
  // Convert both input strings to lowercase if caseInsensitive is enabled.
  if (caseInsensitive) {
    return lower(text).find(lower(pattern)) != std::string::npos;
  }

  return text.find(pattern) != std::string::npos;
}

std::string Search::lower(const std::string &text) {
  std::string result = text;

  // Transform ASCII characters to lowercase in-place.
  std::transform(
      result.begin(), result.end(), result.begin(),
      [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

  return result;
}
