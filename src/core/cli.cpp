#include "include/cli.hpp"

CLIApp::CLIApp(vec<std::shared_ptr<Subcommand>> subcommands)
    : m_app(new CLI::App()) {
  for (auto &subcommand : subcommands) {
    CLI::App *subcmd = subcommand->setup(*this->m_app);
    subcmd->callback([&]() { subcommand->handle(); });
  }
  this->m_app->require_subcommand();
}

int CLIApp::run(int argc, char **argv) {
  CLI11_PARSE(*this->m_app, argc, argv);
  return 0;
}