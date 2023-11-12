#ifndef __FS_API_H
#define __FS_API_H

#include <filesystem>
#include <functional>
#include <vector>

/**
 * @brief find all files recursively from source and subdirectories matching
 * with predicate.
 * @param source root directory where matching starts
 * @param predicate predicate to which files are matching.
 * @returns vector of matched files
 */
std::vector<std::filesystem::path> matchFiles(
    const std::filesystem::path& source,
    const std::function<bool(const std::filesystem::path&)>& predicate);

#endif