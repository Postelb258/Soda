#ifndef __CONFIG_H
#define __CONFIG_H

#include <cstdint>
#include <sys/stat.h>
#include <string_view>
#include <toml.hpp>
#include <toml/get.hpp>
#include <toml/types.hpp>
#include <toml/utility.hpp>
#include <optional>
#include <string>


typedef toml::basic_value<toml::discard_comments, std::unordered_map, std::vector> BasicValue;

struct Package {
    std::string_view name;
    std::string_view entry;
    std::string_view version;
    std::optional<std::string_view> description;

    Package() = default;
    Package(const BasicValue& config, const BasicValue& package);
};

struct Lib {
    static std::optional<Lib> constructOptionally(const BasicValue& config, const BasicValue& lib);
};

struct Debug {
    static std::optional<Debug> constructOptionally(const BasicValue& config, const BasicValue& debug);
};

struct Release {
    uint8_t optimization;

    static std::optional<Release> constructOptionally(const BasicValue& config, const BasicValue& release);
};

struct Dependencies {
    std::pair<std::string_view, std::string_view> deps;

    static std::optional<Dependencies> constructOptionally(const BasicValue& config, const BasicValue& dependencies);
};

struct Config {
    Package package;
    std::optional<Lib> lib;
    std::optional<Debug> debug;
    std::optional<Release> release;
    std::optional<Dependencies> dependencies;

    static std::optional<Config> load(const std::string& path);
    static std::unique_ptr<Config> getLoaded(const std::optional<Config>& opt_config);
};






#endif