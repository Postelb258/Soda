#include "include/clang.hpp"

#include <stdexcept>

Clang::Clang(std::unique_ptr<Config> config) : m_config(std::move(config)) {}

void Clang::build() {
  if (this->m_config == nullptr)
    throw std::runtime_error("Config file is not detected");
}

// LinkStrategy Clang::link() {

// }

void Clang::run() {}

void Clang::makeExecutable() {}

void Clang::makeStaticLibrary() {}

void Clang::makeSharedLibrary() {}
