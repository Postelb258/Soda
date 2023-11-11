cmake_minimum_required(VERSION 3.27.7)
project(Soda VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB CORE_SOURCES "src/core/*.cpp")
file(GLOB SUBCOMMANDS_SOURCES "src/subcommands/*.cpp")
file(GLOB COMPILERS_SOURCES "src/compilers/*.cpp")
add_executable(Soda src/main.cpp ${CORE_SOURCES} ${SUBCOMMANDS_SOURCES} ${COMPILERS_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
