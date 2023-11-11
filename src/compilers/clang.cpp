#include "include/clang.hpp"

Clang::Clang(std::unique_ptr<Config> config, BuildMode build_mode)
    : m_config(std::move(config)), m_mode(build_mode) {}

void Clang::build() {
  if (this->m_config == nullptr)
    throw std::runtime_error("Config file is not detected");

  std::string source = this->m_config->lib ? "lib" : "src";
  std::string cxx =
      std::filesystem::path(this->m_config->package.entry).extension();
  std::vector<std::string> flags =
      getFlagsForCLANG(this->m_config.get(), this->m_mode);

  std::string mode_dir =
      this->m_mode == BuildMode::release ? "release" : "debug";
  std::filesystem::path target("target/__objs/" + mode_dir + "/");
  try {
    std::error_code ec;
    std::filesystem::create_directories(target, ec);
    if (ec) {
      throw std::runtime_error("[error] Failed to create `target`: " +
                               ec.message());
    }
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    std::exit(1);
  }

  std::vector<std::filesystem::path> source_files = matchFiles(
      std::filesystem::path(source), [cxx](const std::filesystem::path& entry) {
        return entry.extension() == cxx;
      });

  Shell* shell = new Shell("clang");
  for (const auto& source_file : source_files) {
    shell->addArg("-x");
    shell->addArg(cxx.find("pp")
                      ? cxx.replace(cxx.find("pp"), sizeof("pp") - 1, "++")
                      : cxx);
    shell->addArgs(flags);
    shell->addArg("-c");
    shell->addArg(source_file.generic_string());
    shell->addArg("-o");
    shell->addArg(target.generic_string() +
                  source_file.stem().generic_string() + ".o");

    shell->run();
    shell->removeArgs();
  }

  delete shell;
}

void Clang::link() {}

void Clang::run() {}
