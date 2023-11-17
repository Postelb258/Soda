#include "include/shell.hpp"

Shell::Shell(const str &command) noexcept : m_command(command), m_args({}) {
  this->m_args.push_back(command);
}

void Shell::addArg(const str &arg) noexcept { this->m_args.push_back(arg); }

void Shell::addArgs(const vec<str> &args) noexcept {
  this->m_args.insert(this->m_args.end(), args.begin(), args.end());
}

void Shell::flushArgs() noexcept { this->m_args.clear(); }

std::string Shell::joinArgs(const str &delimiter) noexcept {
  return std::accumulate(
      this->m_args.begin() + 1, this->m_args.end(), this->m_args[0],
      [&delimiter](const str &a, const str &b) { return a + delimiter + b; });
}

void Shell::run() noexcept {
  str args = Shell::joinArgs(" ");
  system(args.c_str());
}

/* FLAG GET */
vec<str> getFlagsForGNU(std::shared_ptr<Config> config,
                        BuildMode build_mode) noexcept {
  vec<str> flags;

  if (build_mode == BuildMode::debug) {
    if (!config->debug) {
      flags = {"-Wall", "-Wextra", "-Wunreachable-code", "-g", "-O0"};
    } else if (config->debug) {
      flags = {"-Wall", "-Wextra", "-Wunreachable-code", "-g", "-O0"};
    }
  }

  if (build_mode == BuildMode::release) {
    if (!config->release) {
      flags = {"-Wall", "-Wextra", "-Wunreachable-code", "-DNDEBUG", "-O3"};
    } else if (config->release) {
      str optimization = "-O" + std::to_string(config->release->optimization);
      flags = {"-Wall", "-Wextra", "-Wunreachable-code", "-DNDEBUG",
               optimization};
    }
  }
  return flags;
}

vec<str> getFlagsForCLANG(std::shared_ptr<Config> config,
                          BuildMode build_mode) noexcept {
  vec<str> flags;

  if (build_mode == BuildMode::debug) {
    if (!config->debug) {
      flags = {"-Wall", "-Wextra", "-Wunreachable-code",
               "-g",    "-O0",     "-fno-omit-frame-pointer"};
    } else if (config->debug) {
      flags = {"-Wall", "-Wextra", "-Wunreachable-code",
               "-g",    "-O0",     "-fno-omit-frame-pointer"};
    }
  }

  if (build_mode == BuildMode::release) {
    if (!config->release) {
      flags = {"-Wall", "-Wextra", "-Wunreachable-code", "-03", "-flto"};
    } else if (config->release) {
      str optimization = "-O" + std::to_string(config->release->optimization);
      flags = {"-Wall", "-Wextra", "-Wunreachable-code", optimization, "-flto"};
    }
  }

  return flags;
}