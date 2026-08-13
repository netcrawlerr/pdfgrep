#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

struct CliOptions {
  std::string pattern;

  std::vector<std::filesystem::path> paths;

  bool caseInsensitive = false;
  bool recursive = false;
  bool countOnly = false;

  int context = 0;

  bool showHelp = false;
  bool showVersion = false;
};

class Cli {
public:
  static std::optional<CliOptions> parse(int argc, char *argv[]);

  static void printHelp();
  static void printVersion();

private:
  static void printError(const std::string &message);
};
