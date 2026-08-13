#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct PdfPage {
  int number;
  std::string text;
};

class Pdf {
public:
  explicit Pdf(const std::filesystem::path &path);

  bool load();

  [[nodiscard]]
  const std::vector<PdfPage> &pages() const;

  [[nodiscard]]
  const std::string &error() const;

private:
  std::filesystem::path path_;
  std::vector<PdfPage> pages_;
  std::string error_;
};
