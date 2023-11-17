#include "include/config.hpp"

Package Package::deserialize(const opt<Table> &table) {
  if (!table.has_value()) return Package{};

  return Package{.name = table->required<TOML_STR>("name"),
                 .entry = table->required<TOML_STR>("entry"),
                 .version = table->required<TOML_STR>("version"),
                 .description = table->optional<TOML_STR>("description")};
}

opt<Lib> Lib::deserialize(const opt<Table> &table) {
  if (!table.has_value()) return Lib{};

  return Lib{

  };
}

opt<Debug> Debug::deserialize(const opt<Table> &table) {
  if (!table.has_value()) return Debug{};

  return Debug{.optimization = table->required<TOML_INT>("optimization")};
}

opt<Release> Release::deserialize(const opt<Table> &table) {
  if (!table.has_value()) return Release{};

  return Release{.optimization = table->required<TOML_INT>("optimization")};
}

opt<Dependencies> Dependencies::deserialize(const opt<Table> &table) {
  if (!table.has_value()) return Dependencies{};

  return Dependencies{.deps = table.value().get()};
}

opt<Aliases> Aliases::deserialize(const opt<Table> &table) {
  if (!table.has_value()) return Aliases{};

  return Aliases{.aliases = table.value().get()};
}

std::shared_ptr<Config> Config::load(const std::string &path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) return nullptr;

  Config s_config;
  Table config_table = Table(toml::parse(path));
  s_config.package =
      Package::deserialize(config_table.required_table("package"));
  s_config.lib = Lib::deserialize(config_table.optional_table("lib"));
  s_config.debug = Debug::deserialize(config_table.optional_table("debug"));
  s_config.release =
      Release::deserialize(config_table.optional_table("release"));
  s_config.dependencies =
      Dependencies::deserialize(config_table.optional_table("dependencies"));
  s_config.aliases =
      Aliases::deserialize(config_table.optional_table("aliases"));

  return std::make_shared<Config>(s_config);
}
