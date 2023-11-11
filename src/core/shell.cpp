#include "include/shell.hpp"

Shell::Shell(const std::string &command) : m_command(command), m_args({}) {
  this->m_args.push_back(command);
}

void Shell::addArg(const std::string &arg) { this->m_args.push_back(arg); }

void Shell::addArgs(const std::vector<std::string> &args) {
  this->m_args.insert(this->m_args.end(), args.begin(), args.end());
}

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