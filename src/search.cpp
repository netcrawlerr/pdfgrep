#include "../include/search.h"
#include <algorithm>

std::vector<SearchMatch> Search::search(const Pdf &pdf,
                                        const std::string &pattern,
                                        const SearchOptions &options) {
  std::vector<SearchMatch> matches;

  for (const auto &page : pdf.pages()) {
    std::vector<std::string> lines;

    std::stringstream stream(page.text);
    std::string line;

    while (std::getline(stream, line)) {
      lines.push_back(line);
    }

    for (std::size_t i = 0; i < lines.size(); ++i) {
      if (!contains(lines[i], pattern, options.caseInsensitive)) {
        continue;
      }

      SearchMatch match;

      match.page = page.number;
      match.line = lines[i];

      const int context = options.context;

      const int start = std::max(0, static_cast<int>(i) - context);

      const int end = std::min(static_cast<int>(lines.size()) - 1,
                               static_cast<int>(i) + context);

      for (int j = start; j < static_cast<int>(i); ++j) {
        match.contextBefore.push_back(lines[j]);
      }

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
  if (caseInsensitive) {
    return lower(text).find(lower(pattern)) != std::string::npos;
  }

  return text.find(pattern) != std::string::npos;
}

std::string Search::lower(const std::string &text) {
  std::string result = text;

  std::transform(
      result.begin(), result.end(), result.begin(),
      [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

  return result;
}
