#pragma once

#include <filesystem>
#include <string>
#include <vector>

/// @brief Represents an extracted single page from a PDF document.
struct PdfPage {
  /// @brief 1-based page index/number.
  int number;

  /// @brief Extracted plain text content of the page.
  std::string text;
};

/// @brief Handles loading and extracting text content from a PDF file.
class Pdf {
public:
  /// @brief Constructs a PDF reader bound to a target file path.
  /// @param path Path to the source PDF file on the filesystem.
  explicit Pdf(const std::filesystem::path &path);

  /// @brief Opens the PDF file and extracts page content into memory.
  /// @return True if the file was successfully loaded and parsed; false
  /// otherwise.
  bool load();

  /// @brief Retrieves the collection of extracted PDF pages.
  /// @return Const reference to a vector of extracted PdfPage objects.
  [[nodiscard]]
  const std::vector<PdfPage> &pages() const;

  /// @brief Retrieves the last error message if loading or parsing failed.
  /// @return Const reference to the error message string.
  [[nodiscard]]
  const std::string &error() const;

private:
  /// @brief File system path to the target PDF document.
  std::filesystem::path path_;

  /// @brief Storage for extracted page data.
  std::vector<PdfPage> pages_;

  /// @brief Holds internal error details if an operation fails.
  std::string error_;
};
