#ifndef __CONFIG_H
#define __CONFIG_H

#include <sys/stat.h>

#include <map>
#include <memory>
#include <optional>
#include <string>

#include "../../api/include/toml.hpp"

template <typename T>
using opt = std::optional<T>;

/// [package] in TOML Config
struct Package {
  sview name;
  sview entry;
  sview version;
  opt<sview> description;

  static Package deserialize(const opt<Table>& table);
};

/// [lib] in TOML Config
struct Lib {
  static opt<Lib> deserialize(const opt<Table>& table);
};

/// [debug] in TOML Config
struct Debug {
  short optimization;

  static opt<Debug> deserialize(const opt<Table>& table);
};

/// [release] in TOML Config
struct Release {
  short optimization;

  static opt<Release> deserialize(const opt<Table>& table);
};

/// [dependencies] in TOML Config
struct Dependencies {
  smap deps;

  static opt<Dependencies> deserialize(const opt<Table>& table);
};

/// [aliases] in TOML Config
struct Aliases {
  smap aliases;

  static opt<Aliases> deserialize(const opt<Table>& table);
};

template <typename S>
S checkTable(const opt<Table>& table);

/// Deserialized TOML Config
struct Config {
  Package package;
  opt<Lib> lib;
  opt<Debug> debug;
  opt<Release> release;
  opt<Dependencies> dependencies;
  opt<Aliases> aliases;

  static std::unique_ptr<Config> load(const std::string& path);
};

#endif