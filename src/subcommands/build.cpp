#include "include/build.hpp"

Build::Build(std::unique_ptr<Config> config, BuildMode build_mode)
    : m_config(std::move(config)), m_mode(BuildMode::debug) {}

CLI::App* Build::setup(CLI::App& app) {
  CLI::App* sub = app.add_subcommand("build", "builds a project");
  bool release{false};
  sub->add_flag("-r,--release", release, "Builds in a release mode");
  this->m_mode = release ? BuildMode::release : BuildMode::debug;
  return sub;
}

void Build::handle() {
  Clang* clang = new Clang(std::move(this->m_config), this->m_mode);
  clang->build();
  free(clang);
}