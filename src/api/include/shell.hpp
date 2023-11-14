#ifndef __SHELL_H
#define __SHELL_H

#include <numeric>

#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"
#include "../../typedefs.hpp"

/**
 * @brief A builder class for Shell command execution
 *
 */
class Shell {
 private:
  str m_command;
  vec<str> m_args;
  str joinArgs(const std::string& delimiter) noexcept;

 public:
  /**
   * @brief Construct a new Shell object
   *
   * @param command shell command that will be executed
   */
  Shell(const str& command) noexcept;
  /**
   * @brief add argument to command
   *
   * @param arg
   */
  void addArg(const str& arg) noexcept;
  /**
   * @brief add the arguments to command
   *
   * @param args
   */
  void addArgs(const vec<str>& args) noexcept;
  /**
   * @brief clear all arguments
   */
  void flushArgs() noexcept;
  /**
   * @brief run shell command with arguments
   */
  void run() noexcept;
};

/**
 * @brief Get the Flags For GNU compiler according to build mode
 *
 * @param config
 * @param build_mode
 * @return flags
 */
vec<str> getFlagsForGNU(Config* config, BuildMode build_mode) noexcept;
/**
 * @brief Get the Flags For Clang compiler according to build mode
 *
 * @param config
 * @param build_mode
 * @return flags
 */
vec<str> getFlagsForCLANG(Config* config, BuildMode build_mode) noexcept;

#endif