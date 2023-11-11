#ifndef __CLI_H 
#define __CLI_H 

#include <CLI11.hpp>

class Subcommand {
public:
    virtual CLI::App* setup(CLI::App& app) = 0;
    virtual void handle() = 0;
};

class CLIApp {
private:
    std::unique_ptr<CLI::App> m_app;
public:
    CLIApp(std::vector<std::shared_ptr<Subcommand>>& subcommands);
    int run(int argc, char** argv);
};

#endif