#include "include/gnu.hpp"

GNU::GNU(std::unique_ptr<Config> config, BuildMode build_mode)
    : m_config(std::move(config)), m_mode(build_mode) {}

void GNU::build() {
  if (this->m_config == nullptr)
    throw std::runtime_error("Config file is not detected");

  std::string source = this->m_config->lib ? "lib" : "src";
  std::string cxx =
      std::filesystem::path(this->m_config->package.entry).extension();
  std::vector<std::string> flags =
      getFlagsForGNU(this->m_config.get(), this->m_mode);

  std::string mode_dir =
      this->m_mode == BuildMode::release ? "release" : "debug";
  std::filesystem::path target("target/__objs/" + mode_dir + "/");
  std::error_code ec;
  std::filesystem::create_directories(target, ec);
  if (ec) {
    throw std::runtime_error("[error] Failed to create `target`: " +
                             ec.message());
  }

  std::vector<std::filesystem::path> source_files = matchFiles(
      std::filesystem::path(source), [cxx](const std::filesystem::path& entry) {
        return entry.extension() == cxx;
      });

  Shell* shell = new Shell("gcc");
  for (const auto& source_file : source_files) {
    shell->addArg("-x");
    shell->addArg(((cxx.find("pp") != std::string::npos)
                       ? cxx.replace(cxx.find("pp"), sizeof("pp") - 1, "++")
                       : cxx)
                      .erase(0, 1));
    shell->addArgs(flags);
    shell->addArg("-o");
    shell->addArg(target.generic_string() +
                  source_file.stem().generic_string() + ".o");
    shell->addArg(source_file.filename());

    shell->run();
    shell->removeArgs();
  }

  delete shell;
}

void GNU::link() {}

void GNU::run() {}