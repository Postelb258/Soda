#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <filesystem>
#include <map>
#include <optional>
#include <toml.hpp>

typedef toml::basic_value<toml::discard_comments, std::unordered_map,
                          std::vector>
    BasicValue;

typedef std::string str;
typedef std::string_view sview;
typedef std::filesystem::path fs_path;
typedef std::map<std::string_view, std::string_view> smap;

template <typename T>
using opt = std::optional<T>;

template <typename T>
using vec = std::vector<T>;

#endif