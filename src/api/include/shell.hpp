#ifndef __SHELL_H
#define __SHELL_H

#include <cstdint>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"

class Shell {
 private:
  std::string m_command;
  std::vector<std::string> m_args;
  std::string cocain_args(const std::string& delimiter);

 public:
  Shell(const std::string& command);
  void addArg(const std::string& arg);
  void addArgs(const std::vector<std::string>& args);
  void removeArgs();
  void run();
};

std::vector<std::string> getFlagsForGNU(Config* config, BuildMode build_mode);
std::vector<std::string> getFlagsForCLANG(Config* config, BuildMode build_mode);
std::vector<std::string> getFlagsForMSVC(Config* config, BuildMode build_mode);

#endif