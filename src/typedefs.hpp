#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <map>
#include <optional>
#include <toml.hpp>

typedef toml::basic_value<toml::discard_comments, std::unordered_map,
                          std::vector>
    BasicValue;

typedef std::string_view sview;
typedef std::map<std::string_view, std::string_view> smap;

template <typename T>
using opt = std::optional<T>;

#endif