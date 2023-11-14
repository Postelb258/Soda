#ifndef __BUILD_SUBCMD_H
#define __BUILD_SUBCMD_H

#include "../../compilers/include/clang.hpp"
#include "../../core/include/cli.hpp"
#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"
#include "../../typedefs.hpp"

class Build : public Subcommand {
 private:
  std::unique_ptr<Config> m_config;
  BuildMode m_mode;

 public:
  Build(std::unique_ptr<Config> config);
  std::unique_ptr<CLI::App> setup(CLI::App& app) noexcept override;
  void handle() override;
};

#endif