#include "core/include/cli.hpp"
#include "core/include/compilation.hpp"
#include "core/include/config.hpp"
#include "subcommands/include/build.hpp"
#include "subcommands/include/new.hpp"

int main(int argc, char **argv) {
  std::shared_ptr<Config> config = Config::load("./Soda.toml");

  vec<std::shared_ptr<Subcommand>> subcmds = {std::make_shared<New>(),
                                              std::make_shared<Build>(config)};
  std::unique_ptr<CLIApp> app = std::make_unique<CLIApp>(subcmds);
  app->run(argc, argv);
}
