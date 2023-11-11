#include "include/build.hpp"

Build::Build(std::unique_ptr<Config> config) : m_config(std::move(config)) {}

CLI::App* Build::setup(CLI::App& app) {
  CLI::App* sub = app.add_subcommand("build", "builds a project");

  return sub;
}

void Build::handle() {
  Clang* clang = new Clang(std::move(this->m_config));
  clang->build();
  free(clang);
}