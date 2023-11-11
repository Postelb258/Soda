#ifndef __BUILD_SUBCMD_H
#define __BUILD_SUBCMD_H

#include "../../compilers/include/clang.hpp"
#include "../../core/include/cli.hpp"
#include "../../core/include/config.hpp"

class Build : public Subcommand {
 private:
  std::unique_ptr<Config> m_config;

 public:
  Build(std::unique_ptr<Config> config);
  CLI::App* setup(CLI::App& app) override;
  void handle() override;
};

#endif