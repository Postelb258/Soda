#ifndef __GNU_COMPILER_H
#define __GNU_COMPILER_H

#include "../../api/include/fs.hpp"
#include "../../api/include/shell.hpp"
#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"

class GNU : public CompilationStrategy {
 private:
  std::unique_ptr<Config> m_config;
  BuildMode m_mode;

 public:
  GNU(std::unique_ptr<Config> config, BuildMode build_mode);
  void build() override;
  void link() override;
  void run() override;
};

#endif