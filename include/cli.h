#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

/// @brief Holds command-line arguments and configuration flags for the
/// application.
struct CliOptions {
  /// @brief The search target pattern or text string.
  std::string pattern;

  /// @brief Target file or directory paths to search.
  std::vector<std::filesystem::path> paths;

  /// @brief Perform a case-insensitive search if set to true.
  bool caseInsensitive = false;

  /// @brief Traverses directories recursively if set to true.
  bool recursive = false;

  /// @brief Print only the total count of matching lines instead of the
  /// contents.
  bool countOnly = false;

  /// @brief Number of surrounding context lines to display before and after a
  /// match.
  int context = 0;

  /// @brief Flag indicating if the user requested the help text.
  bool showHelp = false;

  /// @brief Flag indicating if the user requested the version information.
  bool showVersion = false;
};

/// @brief Handles command-line argument parsing, validation, and CLI messaging.
class Cli {
public:
  /// @brief Parses command-line arguments into structured options.
  /// @param argc Argument count from main().
  /// @param argv Argument vector from main().
  /// @return A populated CliOptions struct if parsing succeeds, or std::nullopt
  /// if an error occurs or execution should halt (e.g., help/version
  /// displayed).
  static std::optional<CliOptions> parse(int argc, char *argv[]);

  /// @brief Prints usage instructions and available options to standard output.
  static void printHelp();

  /// @brief Prints application version details to standard output.
  static void printVersion();

private:
  /// @brief Formats and outputs an error message to standard error.
  /// @param message Descriptive error message detailing what failed during
  /// parsing.
  static void printError(const std::string &message);
};
