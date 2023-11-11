#ifndef __COMPILATION_H
#define __COMPILATION_H

enum BuildMode { debug, release };

class LinkStrategy {
 public:
  virtual void makeExecutable() = 0;
  virtual void makeStaticLibrary() = 0;
  virtual void makeSharedLibrary() = 0;
};

class CompilationStrategy {
 public:
  virtual void build() = 0;
  virtual void link() = 0;
};

#endif