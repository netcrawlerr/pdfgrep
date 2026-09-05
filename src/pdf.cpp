#include "../include/pdf.h"

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>

Pdf::Pdf(const std::filesystem::path &path) : path_(path) {}

bool Pdf::load() {
  // Clear any existing page state or leftover error messages prior to loading.
  pages_.clear();
  error_.clear();

  // Load the target PDF file into a Poppler document pointer.
  auto document = poppler::document::load_from_file(path_.string());

  if (!document) {
    error_ = "failed to open PDF";
    return false;
  }

  const int pageCount = document->pages();

  // Iterate through pages (Poppler utilizes 0-based page indexing).
  for (int i = 0; i < pageCount; ++i) {
    auto page = document->create_page(i);

    if (!page) {
      continue;
    }

    PdfPage pdfPage;
    // Map zero-indexed Poppler page counter to a human-readable 1-based page
    // number.
    pdfPage.number = i + 1;

    // Extract text content from the current page and convert it to UTF-8
    // encoding.
    const auto text = page->text().to_utf8();

    // Assign character vector range directly into the page's text string
    // container.
    pdfPage.text.assign(text.begin(), text.end());

    pages_.push_back(std::move(pdfPage));
  }

  return true;
}

const std::vector<PdfPage> &Pdf::pages() const { return pages_; }

const std::string &Pdf::error() const { return error_; }
