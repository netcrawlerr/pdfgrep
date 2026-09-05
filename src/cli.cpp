#include "../include/cli.h"

#include <iostream>

std::optional<CliOptions> Cli::parse(int argc, char *argv[]) {
  // Guard clause: Display help text if no arguments were provided.
  if (argc < 2) {
    printHelp();
    return std::nullopt;
  }

  CliOptions options;

  // Process arguments sequentially, skipping executable name at index 0.
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    // Early exit flags - return immediately once matched.
    if (arg == "-h" || arg == "--help") {
      options.showHelp = true;
      return options;
    }

    if (arg == "-v" || arg == "--version") {
      options.showVersion = true;
      return options;
    }

    // Standard boolean toggle flags.
    if (arg == "-i" || arg == "--ignore-case") {
      options.caseInsensitive = true;
      continue;
    }

    if (arg == "-r" || arg == "--recursive") {
      options.recursive = true;
      continue;
    }

    if (arg == "-c" || arg == "--count") {
      options.countOnly = true;
      continue;
    }

    // Option expecting an integer value in the next token slot.
    if (arg == "-C" || arg == "--context") {
      if (i + 1 >= argc) {
        printError("-C requires a number");
        return std::nullopt;
      }

      try {
        // Advance loop index to consume the numerical value token.
        options.context = std::stoi(argv[++i]);

        if (options.context < 0) {
          printError("context cannot be negative");
          return std::nullopt;
        }
      } catch (const std::exception &) {
        printError("invalid context value");
        return std::nullopt;
      }

      continue;
    }

    // Reject unrecognized flag options starting with a hyphen.
    if (!arg.empty() && arg[0] == '-') {
      printError("unknown option: " + arg);
      return std::nullopt;
    }

    // Positional argument handling: first non-option token is target pattern,
    // subsequent positional tokens are target file/directory paths.
    if (options.pattern.empty()) {
      options.pattern = arg;
    } else {
      options.paths.emplace_back(arg);
    }
  }

  // Validate required positional parameters prior to completing parse step.
  if (options.pattern.empty()) {
    printError("no search pattern provided");
    return std::nullopt;
  }

  if (options.paths.empty()) {
    printError("no PDF file or directory provided");
    return std::nullopt;
  }

  return options;
}

void Cli::printHelp() {
  std::cout << "pdfgrep - search text inside PDF files\n\n"
            << "Usage:\n"
            << "  pdfgrep [OPTIONS] PATTERN FILE...\n"
            << "  pdfgrep [OPTIONS] PATTERN DIRECTORY\n\n"
            << "Options:\n"
            << "  -i, --ignore-case       Case-insensitive search\n"
            << "  -r, --recursive         Search directories recursively\n"
            << "  -c, --count             Print match count only\n"
            << "  -C, --context N         Show N lines around matches\n"
            << "  -h, --help              Show this help message\n"
            << "  -v, --version           Show version\n\n"
            << "Examples:\n"
            << "  pdfgrep \"virtual memory\" book.pdf\n"
            << "  pdfgrep -i \"deadlock\" os.pdf\n"
            << "  pdfgrep -r \"mutex\" ~/Documents/books\n"
            << "  pdfgrep -C 2 \"process\" os.pdf\n";
}

void Cli::printVersion() { std::cout << "pdfgrep 0.1.0\n"; }

void Cli::printError(const std::string &message) {
  std::cerr << "pdfgrep: " << message << '\n';
}
