#include "include/build.hpp"

Build::Build(std::unique_ptr<Config> config) : m_config(std::move(config)), m_buildmode(BuildMode::debug) {}

CLI::App* Build::setup(CLI::App& app) {
  CLI::App* sub = app.add_subcommand("build", "builds a project");
  bool release{false};
  sub->add_flag("-r, --release", release, "Builds a release");
  this->m_buildmode = release ? BuildMode::release : BuildMode::debug;
  return sub;
}

void Build::handle() {
  Clang* clang = new Clang(std::move(this->m_config), this->m_buildmode);
  clang->build();
  free(clang);
}