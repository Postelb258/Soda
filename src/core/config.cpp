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
    const BasicValue &dependencies) {
  std::optional<Dependencies> s_dependencies;
  if (dependencies.is_table()) {
    auto dependencies_map =
        toml::find_or<std::pair<std::string_view, std::string_view>>(
            dependencies, "dependencies", {});
    s_dependencies = Dependencies{.deps = dependencies_map};
  }

  return s_dependencies;
}

std::optional<Config> Config::load(const std::string &path) {
  Config s_config;
  struct stat info;

  if (stat(path.c_str(), &info) != 0) {
    return std::optional<Config>();
  };

  auto config = toml::parse(path);
  s_config.package = Package(toml::find<BasicValue>(config, "package"));
  s_config.lib =
      Lib::constructOptionally(toml::find_or<BasicValue>(config, "lib", {}));
  s_config.debug = Debug::constructOptionally(
      toml::find_or<BasicValue>(config, "debug", {}));
  s_config.release = Release::constructOptionally(
      toml::find_or<BasicValue>(config, "release", {}));
  s_config.dependencies = Dependencies::constructOptionally(
      toml::find_or<BasicValue>(config, "dependencies", {}));

  return std::optional<Config>(s_config);
}

std::unique_ptr<Config> Config::getLoaded(
    const std::optional<Config> &opt_config) {
  if (opt_config.has_value())
    return std::make_unique<Config>(opt_config.value());
  else
    return nullptr;
}
