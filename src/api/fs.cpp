#include "include/fs.hpp"

vec<fs_path> matchFiles(
    const fs_path& source,
    const std::function<bool(const fs_path&)> predicate) noexcept {
  vec<fs_path> matched_paths;

  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(source)) {
    if (std::filesystem::is_regular_file(entry) && predicate(entry.path())) {
      matched_paths.push_back(entry.path());
    }
  }

  return matched_paths;
}