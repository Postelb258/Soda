#include "include/build.hpp"

Build::Build(std::shared_ptr<Config> config)
    : m_config(config), m_mode(BuildMode::debug) {}

CLI::App* Build::setup(CLI::App& app) noexcept {
  CLI::App* sub = app.add_subcommand("build", "builds a project");
  bool release{false};
  sub->add_flag("-r,--release", release, "Builds in a release mode");
  this->m_mode = release ? BuildMode::release : BuildMode::debug;
  return sub;
}

void Build::handle() {
  std::unique_ptr<Clang> clang =
      std::make_unique<Clang>(Clang(this->m_config, this->m_mode));
  clang->build();
  clang->link()->makeExecutable();
}