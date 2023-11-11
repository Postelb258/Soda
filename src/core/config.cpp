#include "include/config.hpp"

Package::Package(const BasicValue &package)
    : name(toml::find<std::string_view>(package, "name")),
      entry(toml::find<std::string_view>(package, "entry")),
      version(toml::find<std::string_view>(package, "version")) {
  if (package.contains("description")) {
    description = toml::find<std::string_view>(package, "description");
  }
}

std::optional<Lib> Lib::constructOptionally(const BasicValue &lib) {
  std::optional<Lib> s_lib;
  if (lib.is_table()) s_lib = Lib{};

  return s_lib;
}

std::optional<Debug> Debug::constructOptionally(const BasicValue &debug) {
  std::optional<Debug> s_debug;
  if (debug.is_table()) s_debug = Debug{};

  return s_debug;
}

std::optional<Release> Release::constructOptionally(const BasicValue &release) {
  std::optional<Release> s_release;
  if (release.is_table()) {
    uint8_t optimization = toml::find_or(release, "optimization", 2);
    s_release = Release{.optimization = optimization};
  }

  return s_release;
}

std::optional<Dependencies> Dependencies::constructOptionally(
    const StringPair &dependencies) {
  return std::optional<Dependencies>({.deps = dependencies});
}

std::optional<Aliases> Aliases::constructOptionally(const StringPair &aliases) {
  std::optional<Aliases> s_aliases;
  return std::optional<Aliases>({.aliases = aliases});
}

std::unique_ptr<Config> Config::load(const std::string &path) {
  Config s_config;
  struct stat info;

  if (stat(path.c_str(), &info) != 0) return nullptr;

  BasicValue config = toml::parse(path);
  s_config.package = Package(toml::find<BasicValue>(config, "package"));
  s_config.lib =
      Lib::constructOptionally(toml::find_or<BasicValue>(config, "lib", {}));
  s_config.debug = Debug::constructOptionally(
      toml::find_or<BasicValue>(config, "debug", {}));
  s_config.release = Release::constructOptionally(
      toml::find_or<BasicValue>(config, "release", {}));
  s_config.dependencies = Dependencies::constructOptionally(
      toml::find_or<StringPair>(config, "dependencies", {}));
  s_config.aliases = Aliases::constructOptionally(
      toml::find_or<StringPair>(config, "aliases", {}));
  return std::make_unique<Config>(s_config);
}
