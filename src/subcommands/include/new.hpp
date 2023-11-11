#ifndef __NEW_SUBCMD_H
#define __NEW_SUBCMD_H

#include <bits/stdc++.h>
#include <sys/stat.h>

#include <fstream>
#include <stdexcept>
#include <system_error>

#include "../../core/include/cli.hpp"

class New : public Subcommand {
 private:
  std::string m_path;
  bool m_lib;
  bool m_cxx;

 public:
  New();
  CLI::App* setup(CLI::App& app) override;
  void handle() override;
};

#endif