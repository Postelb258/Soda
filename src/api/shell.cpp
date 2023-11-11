#include "include/shell.hpp"
#include <cstdint>
#include <string>

Shell::Shell(const std::string &command) : m_command(command), m_args({}) {
  this->m_args.push_back(command);
}

void Shell::addArg(const std::string &arg) { this->m_args.push_back(arg); }

void Shell::addArgs(const std::vector<std::string> &args) {
  this->m_args.insert(this->m_args.end(), args.begin(), args.end());
}

void Shell::removeArgs() { this->m_args.clear(); }

std::string Shell::cocain_args(const std::string &delimiter) {
  return std::accumulate(
      this->m_args.begin() + 1, this->m_args.end(), this->m_args[0],
      [&delimiter](const std::string &a, const std::string &b) {
        return a + delimiter + b;
      });
}

void Shell::run() {
  std::string args = Shell::cocain_args(" ");
  system(args.c_str());
}

std::vector<std::string> getFlagsForClang(Config* config, BuildMode build_mode) {
    std::vector<std::string> flags; 
    if (build_mode == BuildMode::debug && !config->debug) {
        flags = {"-g", "-O0", "-fno-omit-frame-pointer"};
    } else if (build_mode == BuildMode::debug && config->debug) {}

    if (build_mode == BuildMode::release && !config->release) {
        flags = {"-O3", "-flto"};
    } else if (build_mode == BuildMode::release && config->release) {
      std::string optimization = "-O" + std::to_string(config->release->optimization);
      flags = {optimization, "-flto"};
    }

    return flags;
}