#ifndef __CLANG_COMPILER_H
#define __CLANG_COMPILER_H

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
};

class ClangLink : public LinkStrategy {
 private:
 public:
  ClangLink();
  void makeExecutable();
  void makeStaticLibrary();
  void makeSharedLibrary();
};

#endif