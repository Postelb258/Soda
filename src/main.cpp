#include "core/include/cli.hpp"
#include "core/include/compilation.hpp"
#include "core/include/config.hpp"
#include "subcommands/include/build.hpp"
#include "subcommands/include/new.hpp"

int main(int argc, char **argv) {
  std::unique_ptr<Config> config = Config::load("./Soda.toml");

  std::vector<std::unique_ptr<Subcommand>> subcmds{
      std::make_unique<New>(), std::make_unique<Build>(std::move(config))};
  std::unique_ptr<CLIApp> app = std::make_unique<CLIApp>(subcmds);
  app->run(argc, argv);
}
