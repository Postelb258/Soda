#ifndef __CLANG_COMPILER_H
#define __CLANG_COMPILER_H

#include "../../api/include/fs.hpp"
#include "../../api/include/shell.hpp"
#include "../../core/include/compilation.hpp"
#include "../../core/include/config.hpp"

class Clang : public CompilationStrategy {
 private:
  std::shared_ptr<Config> m_config;
  BuildMode m_mode;

 public:
  Clang(std::shared_ptr<Config> config, BuildMode build_mode);
  void build() override;
  std::unique_ptr<LinkStrategy> link() override;
};

class ClangLink : public LinkStrategy {
 private:
  fs_path m_location;
  std::shared_ptr<Config> m_config;
  std::unique_ptr<Shell> m_shell;

 public:
  ClangLink(std::shared_ptr<Config> config, std::unique_ptr<Shell> shell,
            const str& mode_dir);
  void makeExecutable();
  void makeStaticLibrary();
  void makeSharedLibrary();
};

#endif