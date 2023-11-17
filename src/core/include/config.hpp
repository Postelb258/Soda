#ifndef __CONFIG_H
#define __CONFIG_H

#include <sys/stat.h>

#include "../../api/include/toml.hpp"

/// [package] in TOML Config
struct Package {
  TOML_STR name;
  TOML_STR entry;
  TOML_STR version;
  opt<TOML_STR> description;

  static Package deserialize(const opt<Table>& table);
};

/// [lib] in TOML Config
struct Lib {
  static opt<Lib> deserialize(const opt<Table>& table);
};

/// [debug] in TOML Config
struct Debug {
  TOML_INT optimization;

  static opt<Debug> deserialize(const opt<Table>& table);
};

/// [release] in TOML Config
struct Release {
  TOML_INT optimization;

  static opt<Release> deserialize(const opt<Table>& table);
};

/// [dependencies] in TOML Config
struct Dependencies {
  TOML_MAP deps;

  static opt<Dependencies> deserialize(const opt<Table>& table);
};

/// [aliases] in TOML Config
struct Aliases {
  TOML_MAP aliases;

  static opt<Aliases> deserialize(const opt<Table>& table);
};

/// Deserialized TOML Config
struct Config {
  Package package;
  opt<Lib> lib;
  opt<Debug> debug;
  opt<Release> release;
  opt<Dependencies> dependencies;
  opt<Aliases> aliases;

  static std::shared_ptr<Config> load(const std::string& path);
};

#endif