#pragma once

#include "pdf.h"

#include <string>
#include <vector>

/// @brief Configuration settings controlling search matching behavior and
/// context capture.
struct SearchOptions {
  /// @brief Ignore letter casing during pattern matching if set to true.
  bool caseInsensitive = false;

  /// @brief Number of preceding and succeeding lines to capture around a
  /// matching line.
  int context = 0;
};

/// @brief Represents a single pattern match found within a PDF document.
struct SearchMatch {
  /// @brief Page number where the match was identified.
  int page;

  /// @brief Content of the specific line containing the match.
  std::string line;

  /// @brief Surrounding lines located directly before the matching line.
  std::vector<std::string> contextBefore;

  /// @brief Surrounding lines located directly after the matching line.
  std::vector<std::string> contextAfter;
};

/// @brief Provides text searching capabilities over PDF document contents.
class Search {
public:
  /// @brief Searches through a loaded PDF object for occurrences of a given
  /// pattern string.
  /// @param pdf Loaded Pdf instance containing page text data.
  /// @param pattern Target substring or pattern to search for within page text.
  /// @param options Search parameters such as case sensitivity and context line
  /// count.
  /// @return A vector of SearchMatch objects detailing every matching location
  /// found.
  static std::vector<SearchMatch> search(const Pdf &pdf,
                                         const std::string &pattern,
                                         const SearchOptions &options);

private:
  /// @brief Checks whether a substring pattern exists within a text string.
  /// @param text Source text line to inspect.
  /// @param pattern Target substring to search for.
  /// @param caseInsensitive If true, performs case-insensitive comparisons.
  /// @return True if the pattern is found within text; false otherwise.
  static bool contains(const std::string &text, const std::string &pattern,
                       bool caseInsensitive);

  /// @brief Converts an ASCII string to lowercase.
  /// @param text Source string to convert.
  /// @return Lowercase copy of the input string.
  static std::string lower(const std::string &text);
};
