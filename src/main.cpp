#include "core/include/cli.hpp"
#include "core/include/compilation.hpp"
#include "core/include/config.hpp"
#include "subcommands/include/new.hpp"
#include "subcommands/include/build.hpp"

int main(int argc, char **argv) {
  std::unique_ptr<Config> config = Config::getLoaded(Config::load("Soda.toml"));

  std::vector<std::shared_ptr<Subcommand>> subcmds{std::make_shared<New>(), std::make_shared<Build>()};
  std::unique_ptr<CLIApp> app = std::make_unique<CLIApp>(subcmds);
  app->run(argc, argv);
}
