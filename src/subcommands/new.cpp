#include "include/new.hpp"

New::New() {}

std::unique_ptr<CLI::App> New::setup(CLI::App& app) noexcept {
  CLI::App* sub = app.add_subcommand("new", "Creates a new Soda project");
  sub->add_option("path", this->m_path, "Specifies the path of project")
      ->required(true)
      ->default_str(".");

  sub->add_flag("-l,--lib", this->m_lib, "Use a library template");

  sub->add_flag("--cxx", this->m_cxx, "Use a CXX template");

  return std::unique_ptr<CLI::App>(sub);
}

void New::handle() {
  str src = this->m_lib ? "lib" : "src";
  str cxx = this->m_cxx ? "cpp" : "c";

  fs_path dirs_path(this->m_path + "/" + src);
  std::error_code ec;
  std::filesystem::create_directories(dirs_path, ec);
  if (ec) {
    throw std::runtime_error("[error] Failed to create directories: " +
                             ec.message());
  }

  fs_path config_path(this->m_path + "/Soda.toml");
  std::ofstream config_file(config_path);

  fs_path entry_path(this->m_path + "/" + src + "/main." + cxx);
  std::ofstream entry_file(entry_path);

  str lib_table = this->m_lib ? "[lib]" : "";
  if (config_file.is_open() && entry_file.is_open()) {
    config_file << "[package]\n"
                   "name = \"" +
                       dirs_path.parent_path().filename().generic_string() +
                       "\""
                       "\n"
                       "entry = \"main." +
                       cxx +
                       "\""
                       "\n"
                       "version = \"0.1.0\"\n" +
                       lib_table
                << std::endl;
    entry_file << "#include <stdio.h>\n"
                  "\n"
                  "int main(void) {\n"
                  "\tprintf(\"Hi, dad\");\n"
                  "\treturn 0;\n"
                  "}"
               << std::endl;
    config_file.close();
    entry_file.close();
  }
}