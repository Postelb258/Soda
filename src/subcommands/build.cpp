#include "include/build.hpp"

Build::Build(std::unique_ptr<Config> config)
    : m_config(std::move(config)), m_mode(BuildMode::debug) {}

std::unique_ptr<CLI::App> Build::setup(CLI::App& app) noexcept {
  CLI::App* sub = app.add_subcommand("build", "builds a project");
  bool release{false};
  sub->add_flag("-r,--release", release, "Builds in a release mode");
  this->m_mode = release ? BuildMode::release : BuildMode::debug;
  return std::unique_ptr<CLI::App>(sub);
}

void Build::handle() {
  std::unique_ptr<Clang> clang =
      std::make_unique<Clang>(Clang(std::move(this->m_config), this->m_mode));
  clang->build();
  clang->link()->makeExecutable();
}