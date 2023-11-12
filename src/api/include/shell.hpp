#ifndef __SHELL_H
#define __SHELL_H

#include <numeric>

#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"

/**
 * @brief A builder class for Shell command execution
 *
 */
class Shell {
 private:
  std::string m_command;
  std::vector<std::string> m_args;
  std::string cocain_args(const std::string& delimiter);

 public:
  /**
   * @brief Construct a new Shell object
   *
   * @param command shell command that will be executed
   */
  Shell(const std::string& command);
  /**
   * @brief add argument to command
   *
   * @param arg
   */
  void addArg(const std::string& arg);
  /**
   * @brief add the arguments to command
   *
   * @param args
   */
  void addArgs(const std::vector<std::string>& args);
  /**
   * @brief clear all arguments
   */
  void flushArgs();
  /**
   * @brief run shell command with arguments
   */
  void run();
};

/**
 * @brief Get the Flags For GNU compiler according to build mode
 *
 * @param config
 * @param build_mode
 * @return flags
 */
std::vector<std::string> getFlagsForGNU(Config* config, BuildMode build_mode);
std::vector<std::string> getFlagsForCLANG(Config* config, BuildMode build_mode);

#endif