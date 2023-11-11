#ifndef __CLANG_COMPILER_H
#define __CLANG_COMPILER_H

#include <iostream>

#include "../../api/include/fs.hpp"
#include "../../api/include/shell.hpp"
#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"

class Clang : public CompilationStrategy {
 private:
  std::unique_ptr<Config> m_config;
  BuildMode m_mode;

 public:
  Clang(std::unique_ptr<Config> config, BuildMode build_mode);
  void build() override;
  void link() override;
  void run() override;
};

#endif