#include "include/config.hpp"

Package Package::deserialize(const opt<Table> &table) {
  checkTable<Package>(table);

  return Package{.name = table->required<sview>("name"),
                 .entry = table->required<sview>("entry"),
                 .version = table->required<sview>("version"),
                 .description = table->optional<sview>("description")};
}

opt<Lib> Lib::deserialize(const opt<Table> &table) {
  checkTable<Lib>(table);

  return Lib{

  };
}

opt<Debug> Debug::deserialize(const opt<Table> &table) {
  checkTable<Debug>(table);

  return Debug{.optimization = table->required<short>("optimization")};
}

opt<Release> Release::deserialize(const opt<Table> &table) {
  checkTable<Release>(table);

  return Release{.optimization = table->required<short>("optimization")};
}

opt<Dependencies> Dependencies::deserialize(const opt<Table> &table) {
  checkTable<Dependencies>(table);

  return Dependencies{.deps = table->required<smap>("dependencies")};
}

opt<Aliases> Aliases::deserialize(const opt<Table> &table) {
  checkTable<Aliases>(table);

  return Aliases{.aliases = table->required<smap>("aliases")};
}

template <typename S>
S checkTable(const opt<Table> &table) {
  if (!table.has_value()) return S{};
}

std::unique_ptr<Config> Config::load(const std::string &path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) return nullptr;

  Config s_config;
  Table config_table = Table(toml::parse(path));
  s_config.package =
      Package::deserialize(config_table.required_table("package"));
  s_config.lib = Lib::deserialize(config_table.optional_table("lib"));
  s_config.debug =
      Debug::deserialize(config_table.optional_table("debug").value());
  s_config.release =
      Release::deserialize(config_table.optional_table("release").value());
  s_config.dependencies = Dependencies::deserialize(
      config_table.optional_table("dependencies").value());
  s_config.aliases =
      Aliases::deserialize(config_table.optional_table("aliases").value());

  return std::make_unique<Config>(s_config);
}
