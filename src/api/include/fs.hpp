#ifndef __FS_API_H
#define __FS_API_H

#include <vector>
#include <filesystem>
#include <functional>

std::vector<std::filesystem::path> matchFiles(const std::filesystem::path& source, const std::function<bool(std::filesystem::path&)>& predicate);

#endif