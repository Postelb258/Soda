#ifndef __FS_API_H
#define __FS_API_H

#include <filesystem>
#include <functional>
#include <vector>

std::vector<std::filesystem::path> matchFiles(
    const std::filesystem::path& source,
    const std::function<bool(const std::filesystem::path&)>& predicate);

#endif