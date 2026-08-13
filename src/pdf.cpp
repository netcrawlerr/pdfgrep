#include "../include/pdf.h"

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>

Pdf::Pdf(const std::filesystem::path &path) : path_(path) {}

bool Pdf::load() {
  pages_.clear();
  error_.clear();

  auto document = poppler::document::load_from_file(path_.string());

  if (!document) {
    error_ = "failed to open PDF";
    return false;
  }

  const int pageCount = document->pages();

  for (int i = 0; i < pageCount; ++i) {
    auto page = document->create_page(i);

    if (!page) {
      continue;
    }

    PdfPage pdfPage;
    pdfPage.number = i + 1;

    const auto text = page->text().to_utf8();

    pdfPage.text.assign(text.begin(), text.end());

    pages_.push_back(std::move(pdfPage));
  }

  return true;
}

const std::vector<PdfPage> &Pdf::pages() const { return pages_; }

const std::string &Pdf::error() const { return error_; }
