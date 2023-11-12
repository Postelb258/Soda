#include "include/clang.hpp"

#include <string>

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
  std::filesystem::path target("target/" + mode_dir + "/__objs/");
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

  Shell* shell = new Shell("clang");
  for (const auto& source_file : source_files) {
    shell->addArg("-x");
    shell->addArg(((cxx.find("pp") != std::string::npos)
                       ? cxx.replace(cxx.find("pp"), sizeof("pp") - 1, "++")
                       : cxx)
                      .erase(0, 1));
    shell->addArgs(flags);
    shell->addArg("-c");
    shell->addArg(source_file.generic_string());
    shell->addArg("-o");
    shell->addArg(target.generic_string() +
                  source_file.stem().generic_string() + ".o");

    shell->run();
    shell->flushArgs();
  }

  delete shell;
}

std::shared_ptr<LinkStrategy> Clang::link() {
  std::string mode_dir =
      this->m_mode == BuildMode::release ? "release" : "debug";
  std::vector<std::filesystem::path> object_file_paths = matchFiles(
      "target/" + mode_dir + "/__objs", [](const std::filesystem::path& entry) {
        return entry.extension() == ".o";
      });

  Shell* shell = new Shell("clang");
  for (auto& object_path : object_file_paths) {
    shell->addArg(object_path.generic_string());
  }
  shell->addArg("-o");
  return std::make_unique<ClangLink>(std::move(this->m_config), shell,
                                     mode_dir);
}

ClangLink::ClangLink(std::unique_ptr<Config> config, Shell* shell,
                     const std::string& mode_dir)
    : m_config(std::move(config)),
      m_shell(shell),
      m_location(std::filesystem::path("target/" + mode_dir + "/")) {}
ClangLink::~ClangLink() { delete this->m_shell; }

void ClangLink::makeExecutable() {
  this->m_shell->addArg(this->m_location.generic_string() +
                        std::string(this->m_config->package.name) +
                        EXE_EXTENSION);
  this->m_shell->run();
}

void ClangLink::makeStaticLibrary() {
  this->m_shell->addArg(this->m_location.generic_string() +
                        std::string(this->m_config->package.name) +
                        STATIC_LIBRARY_EXTENSION);
}

void ClangLink::makeSharedLibrary() {
  this->m_shell->addArg(this->m_location.generic_string() +
                        std::string(this->m_config->package.name) +
                        SHARED_LIBRARY_EXTENSION);
}
