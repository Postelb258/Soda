#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <filesystem>
#include <map>
#include <optional>
#include <toml.hpp>

typedef toml::basic_value<toml::discard_comments, std::unordered_map,
                          std::vector>
    BasicValue;
typedef toml::string TOML_STR;
typedef toml::integer TOML_INT;
typedef toml::table TOML_MAP;

typedef std::string str;
typedef std::filesystem::path fs_path;

template <typename T>
using opt = std::optional<T>;

template <typename T>
using vec = std::vector<T>;

#endif