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

str getLanguageFromExtension(
    const str& _extension
) {
  size_t extension_dot_pos = _extension.find_last_of(".");
  if (extension_dot_pos != str::npos) {
    str extension = _extension.substr(extension_dot_pos + 1);
    if (extension == "c")
      return "c";
    else if (extension == "cpp")
      return "c++";
    else
      throw std::runtime_error("[error] `"+extension+"` is not supported");
  } else {
    throw std::runtime_error("[error] extension dot is not found");
  }
}