#ifndef __MSVC_COMPILER_H
#define __MSVC_COMPILER_H

#include "../../api/include/fs.hpp"
#include "../../api/include/shell.hpp"
#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"

class MSVC : public CompilationStrategy {
 private:
  std::unique_ptr<Config> m_config;
  BuildMode m_mode;

 public:
  MSVC(std::unique_ptr<Config> config, BuildMode build_mode);
  void build() override;
  void link() override;
  void run() override;
};

#endif