#ifndef __CLANG_COMPILER_H
#define __CLANG_COMPILER_H

#include "../../core/include/config.hpp"
#include "../../core/include/compilation.hpp"

class Clang : public CompilationStrategy, public LinkStrategy {
private:
    std::unique_ptr<Config> m_config;
public:
    Clang(std::unique_ptr<Config> config);
    void build() override;
    LinkStrategy link() override;
    void run() override; 

    void makeExecutable() override; 
    void makeStaticLibrary() override;
    void makeSharedLibrary() override;
};

#endif