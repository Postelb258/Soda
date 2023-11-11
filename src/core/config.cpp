#include "include/config.hpp"

Package::Package(const BasicValue& config, const BasicValue& package)
    : name(toml::find<std::string_view>(package, "name")),
      entry(toml::find<std::string_view>(package, "entry")),
      version(toml::find<std::string_view>(package, "version")) {
    
    if (package.contains("description")) {
        description = toml::find<std::string_view>(package, "description");
    }
}

std::optional<Lib> Lib::constructOptionally(
    const BasicValue& config, 
    const BasicValue &lib
    ) {
    std::optional<Lib> s_lib;
    if (config.contains("lib"))
         s_lib = Lib {};

    return s_lib;
}

std::optional<Debug> Debug::constructOptionally(
    const BasicValue &config, const BasicValue &debug
    ) {
    std::optional<Debug> s_debug;
    if (config.contains("debug"))
        s_debug = Debug {}; 

    return s_debug;
}

std::optional<Release> Release::constructOptionally(
    const BasicValue &config, 
    const BasicValue &release
    ) {
    std::optional<Release> s_release;
    if (config.contains("release")) {
        uint8_t optimization = toml::find_or(release, "optimization", 2);
        s_release = Release { .optimization = optimization };
    }

    return s_release;
}

std::optional<Dependencies> Dependencies::constructOptionally(
    const BasicValue &config, 
    const BasicValue &dependencies
    ) {
    std::optional<Dependencies> s_dependencies;
    if (config.contains("dependencies")) {
        auto dependencies_map = toml::find_or<
        std::pair<std::string_view, std::string_view>>(dependencies, "dependencies", {});
        s_dependencies = Dependencies { .deps = dependencies_map };
    }

    return s_dependencies;
}

std::optional<Config> Config::load(const std::string& path) {
    std::optional<Config> s_config;
    struct stat info;

    if (stat(path.c_str(), &info) != 0) 
        return s_config;

    auto config = toml::parse(path);

    s_config->package = Package(config, toml::find<BasicValue>(
        config, "package"
        ));
    s_config->lib = Lib::constructOptionally(config, toml::find<BasicValue>(
        config, "lib"
        ));
    s_config->debug = Debug::constructOptionally(config, toml::find<BasicValue>(
        config, "debug"
        ));
    s_config->release = Release::constructOptionally(config, toml::find<BasicValue>(
        config, "release"
        ));
    s_config->dependencies = Dependencies::constructOptionally(config, toml::find<BasicValue>(
        config, "dependencies"
        ));

    return s_config;
}

std::unique_ptr<Config> Config::getLoaded(const std::optional<Config> &opt_config) {
    if (opt_config.has_value()) 
        return std::make_unique<Config>(opt_config.value());
    else
        return nullptr;
}