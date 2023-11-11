#ifndef __NEW_SUBCMD_H
#define __NEW_SUBCMD_H

#include "../../core/include/cli.hpp"
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>

class New : public Subcommand {
private:
    std::string path;
    bool lib;
    bool cxx;
public:
    New();
    CLI::App* setup(CLI::App& app) override;
    void handle() override;
};

#endif