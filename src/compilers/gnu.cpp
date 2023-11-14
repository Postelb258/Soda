#include "include/gnu.hpp"

GNU::GNU(std::unique_ptr<Config> config, BuildMode build_mode)
    : m_config(std::move(config)), m_mode(build_mode) {}

void GNU::build() {
  if (this->m_config == nullptr)
    throw std::runtime_error("Config file is not detected");

  str source = this->m_config->lib ? "lib" : "src";
  str cxx =
      fs_path(this->m_config->package.entry).extension();
  vec<str> flags =
      getFlagsForGNU(this->m_config.get(), this->m_mode);

  str mode_dir =
      this->m_mode == BuildMode::release ? "release" : "debug";
  fs_path target("target/" + mode_dir + "/__objs/");
  std::error_code ec;
  std::filesystem::create_directories(target, ec);
  if (ec) {
    throw std::runtime_error("[error] Failed to create `target`: " +
                             ec.message());
  }

  vec<fs_path> source_files = matchFiles(
      fs_path(source), [cxx](const fs_path& entry) {
        return entry.extension() == cxx;
      });

  std::unique_ptr<Shell> shell = std::make_unique<Shell>(Shell("gcc"));
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
    shell->flushArgs();
  }
}

std::unique_ptr<LinkStrategy> GNU::link() {
  str mode_dir =
      this->m_mode == BuildMode::release ? "release" : "debug";
  vec<fs_path> object_file_paths = matchFiles(
      "target/" + mode_dir + "/__objs", [](const fs_path& entry) {
        return entry.extension() == ".o";
      });

  std::unique_ptr<Shell> shell = std::make_unique<Shell>(Shell("gcc"));
  for (auto& object_path : object_file_paths) {
    shell->addArg(object_path.generic_string());
  }
  shell->addArg("-o");
  return std::make_unique<GNULink>(std::move(this->m_config), std::move(shell), mode_dir);
}

GNULink::GNULink(std::unique_ptr<Config> config, std::unique_ptr<Shell> shell,
                 const str& mode_dir)
    : m_config(std::move(config)),
      m_shell(std::move(shell)),
      m_location(fs_path("target/" + mode_dir + "/")) {}

void GNULink::makeExecutable() {
  this->m_shell->addArg(this->m_location.generic_string() +
                        str(this->m_config->package.name) +
                        EXE_EXTENSION);
  this->m_shell->run();
}

void GNULink::makeStaticLibrary() {
  // this->m_shell->addArg(this->m_location.generic_string() +
  //                       str(this->m_config->package.name) +
  //                       EXE_EXTENSION);
}

void GNULink::makeSharedLibrary() {
  // this->m_shell->addArg(this->m_location.generic_string() +
  //                       str(this->m_config->package.name) +
  //                       EXE_EXTENSION);
}