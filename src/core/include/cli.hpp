#ifndef __CLI_H
#define __CLI_H

#include <CLI11.hpp>
#include "../../typedefs.hpp"

/**
 * @brief Interface has to be implemented for Subcommand
 *
 */
class Subcommand {
 public:
  /**
   * @brief Implements the build and parse of subcommand with `CLI11` library
   *
   * @param app reference to App from `CLI11` library
   * @return pointer to inner subcommand from `CLI11` library
   */
  virtual std::unique_ptr<CLI::App> setup(CLI::App& app) noexcept = 0;
  /**
   * @brief Handles subcommand after its parsing via callback
   */
  virtual void handle() = 0;
};

/**
 * @brief CLI Application wrapper for `CLI11` library
 */
class CLIApp {
 private:
  std::unique_ptr<CLI::App> m_app;

 public:
  /**
   * @brief Construct a new CLIApp object
   *
   * @param subcommands
   */
  CLIApp(vec<std::unique_ptr<Subcommand>> subcommands);
  /**
   * @brief Runs handling of CLI
   *
   * @param argc number of arguments
   * @param argv arguments
   * @return error code
   */
  int run(int argc, char** argv);
};

#endif