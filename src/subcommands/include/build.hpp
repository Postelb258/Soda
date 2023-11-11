#ifndef __BUILD_SUBCMD_H
#define __BUILD_SUBCMD_H

#include "../../core/include/cli.hpp"
#include "../../core/include/config.hpp"
#include "../../compilers/include/clang.hpp"

class Build : public Subcommand {
private: 
    BuildMode m_buildmode;
    std::unique_ptr<Config> m_config;
public:
    Build(std::unique_ptr<Config> config);
    CLI::App* setup(CLI::App& app) override;
    void handle() override;
};

#endif