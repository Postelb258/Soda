#ifndef __SHELL_H
#define __SHELL_H

#include <functional>
#include <numeric>
#include <vector>
#include <string> 

class Shell {
private:
    std::string m_command;
    std::vector<std::string> m_args;
public:
    Shell(const std::string& command);
    void addArg(const std::string& arg);
    void addArgs(const std::vector<std::string>& args);
    std::string cocain_args(const std::string& delimiter);
    void run();
};

#endif