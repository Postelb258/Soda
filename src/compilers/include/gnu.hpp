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
  std::shared_ptr<LinkStrategy> link() override;
};

class GNULink : public LinkStrategy {
 private:
  std::filesystem::path m_location;
  std::unique_ptr<Config> m_config;
  Shell* m_shell;

 public:
  GNULink(std::unique_ptr<Config> config, Shell* shell,
          const std::string& mode_dir);
  virtual ~GNULink();
  void makeExecutable();
  void makeStaticLibrary();
  void makeSharedLibrary();
};

#endif