#include "include/fs.hpp"

std::vector<std::filesystem::path> matchFiles(
    const std::filesystem::path& source,
    const std::function<bool(const std::filesystem::path&)>& predicate) {
  std::vector<std::filesystem::path> matched_paths;

  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(source)) {
    if (std::filesystem::is_regular_file(entry) && predicate(entry.path())) {
      matched_paths.push_back(entry.path());
    }
  }

  return matched_paths;
}