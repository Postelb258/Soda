#ifndef __COMPILATION_H
#define __COMPILATION_H

#ifdef _WIN32
#define EXE_EXTENSION ".exe"
#define SHARED_LIBRARY_EXTENSION ".dll"
#define STATIC_LIBRARY_EXTENSION ".lib"
#elif __APPLE__
#define EXE_EXTENSION ""
#define SHARED_LIBRARY_EXTENSION ".dylib"
#define STATIC_LIBRARY_EXTENSION ".a"
#else  // Linux/Unix
#define EXE_EXTENSION ""
#define SHARED_LIBRARY_EXTENSION ".so"
#define STATIC_LIBRARY_EXTENSION ".a"
#endif

enum OutObjectType { exe, static_library, shared_library };
enum BuildMode { debug, release };

/**
 * @brief Interface to be implemented by compiler.
 * Has to be for choosing output object type
 * @see OutObjectType
 */
class LinkStrategy {
 public:
  virtual void makeExecutable() = 0;
  virtual void makeStaticLibrary() = 0;
  virtual void makeSharedLibrary() = 0;
};

/**
 * @brief Interface to be implemented by compiler.
 * Has to be for build & link
 */
class CompilationStrategy {
 public:
  virtual void build() = 0;
  virtual void link() = 0;
};

#endif