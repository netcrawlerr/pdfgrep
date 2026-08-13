#include "../include/cli.h"
#include "../include/pdf.h"
#include "../include/scanner.h"
#include "../include/search.h"

#include <iostream>

int main(int argc, char *argv[]) {
  auto parsed = Cli::parse(argc, argv);

  if (!parsed) {
    return 1;
  }

  const CliOptions &options = *parsed;

  if (options.showHelp) {
    Cli::printHelp();
    return 0;
  }

  if (options.showVersion) {
    Cli::printVersion();
    return 0;
  }

  SearchOptions searchOptions;

  searchOptions.caseInsensitive = options.caseInsensitive;

  searchOptions.context = options.context;

  int totalMatches = 0;

  for (const auto &path : options.paths) {
    auto files = Scanner::scan(path, options.recursive);

    if (files.empty()) {
      std::cerr << "pdfgrep: no PDF files found: " << path << '\n';

      continue;
    }

    for (const auto &file : files) {
      Pdf pdf(file);

      if (!pdf.load()) {
        std::cerr << "pdfgrep: " << file << ": " << pdf.error() << '\n';

        continue;
      }

      auto matches = Search::search(pdf, options.pattern, searchOptions);

      totalMatches += static_cast<int>(matches.size());

      if (options.countOnly) {
        std::cout << file << ": " << matches.size() << '\n';

        continue;
      }

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

  return totalMatches > 0 ? 0 : 1;
}
