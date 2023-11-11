#ifndef __CONFIG_H
#define __CONFIG_H

#include <sys/stat.h>

#include <optional>
#include <string>
#include <toml.hpp>

typedef toml::basic_value<toml::discard_comments, std::unordered_map,
                          std::vector>
    BasicValue;

typedef std::pair<std::string_view, std::string_view> StringPair;

struct Package {
  std::string_view name;
  std::string_view entry;
  std::string_view version;
  std::optional<std::string_view> description;

  Package() = default;
  Package(const BasicValue& package);
};

struct Lib {
  static std::optional<Lib> constructOptionally(const BasicValue& lib);
};

struct Debug {
  static std::optional<Debug> constructOptionally(const BasicValue& debug);
};

struct Release {
  uint8_t optimization;
  static std::optional<Release> constructOptionally(const BasicValue& release);
};

struct Dependencies {
  StringPair deps;

  static std::optional<Dependencies> constructOptionally(
      const StringPair& dependencies);
};

struct Aliases {
  StringPair aliases;

  static std::optional<Aliases> constructOptionally(
    const StringPair& aliases);
};

struct Config {
  Package package;
  std::optional<Lib> lib;
  std::optional<Debug> debug;
  std::optional<Release> release;
  std::optional<Dependencies> dependencies;
  std::optional<Aliases> aliases;

  static std::optional<Config> load(const std::string& path);
  static std::unique_ptr<Config> getLoaded(
      const std::optional<Config>& opt_config);
};

#endif