#include "../include/cli.h"
#include "../include/pdf.h"
#include "../include/scanner.h"
#include "../include/search.h"

#include <iostream>

int main(int argc, char *argv[]) {
  // Parse command-line input into structured options.
  auto parsed = Cli::parse(argc, argv);

  // Exit with non-zero status if argument parsing encountered an error.
  if (!parsed) {
    return 1;
  }

  const CliOptions &options = *parsed;

  // Handle early-exit flag checks prior to execution logic.
  if (options.showHelp) {
    Cli::printHelp();
    return 0;
  }

  if (options.showVersion) {
    Cli::printVersion();
    return 0;
  }

  // Map application CLI options into internal search settings.
  SearchOptions searchOptions;
  searchOptions.caseInsensitive = options.caseInsensitive;
  searchOptions.context = options.context;

  int totalMatches = 0;

  // Iterate over each target path supplied by the user.
  for (const auto &path : options.paths) {
    // Resolve path into a collection of target PDF file locations.
    auto files = Scanner::scan(path, options.recursive);

    if (files.empty()) {
      std::cerr << "pdfgrep: no PDF files found: " << path << '\n';
      continue;
    }

    // Process each discovered PDF file sequentially.
    for (const auto &file : files) {
      Pdf pdf(file);

      // Attempt to open and extract page contents.
      if (!pdf.load()) {
        std::cerr << "pdfgrep: " << file << ": " << pdf.error() << '\n';
        continue;
      }

      // Execute search query across the extracted PDF content.
      auto matches = Search::search(pdf, options.pattern, searchOptions);
      totalMatches += static_cast<int>(matches.size());

      // If count-only flag is set, output match total for the file and skip
      // detailed reporting.
      if (options.countOnly) {
        std::cout << file << ": " << matches.size() << '\n';
        continue;
      }

      // Print individual matches along with optional context lines.
      for (const auto &match : matches) {
        std::cout << file << ':' << match.page << ": " << match.line << '\n';

        if (options.context > 0) {
          for (const auto &line : match.contextBefore) {
            std::cout << "  " << line << '\n';
          }

          for (const auto &line : match.contextAfter) {
            std::cout << "  " << line << '\n';
          }
        }
      }
    }
  }

  // Return status 0 (success) if at least one match was found across all
  // targets; otherwise 1.
  return totalMatches > 0 ? 0 : 1;
}
