#ifndef __FS_API_H
#define __FS_API_H

#include <filesystem>
#include <functional>
#include <vector>

#include "../../typedefs.hpp"

/**
 * @brief find all files recursively from source and subdirectories matching
 * with predicate.
 * @param source root directory where matching starts
 * @param predicate predicate to which files are matching.
 * @returns vector of matched files
 */
vec<fs_path> matchFiles(
    const fs_path& source,
    const std::function<bool(const fs_path&)> predicate) noexcept;

#endif