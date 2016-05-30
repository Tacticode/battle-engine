#include <iostream>
#include <cstdlib>
#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/utils/utils.hpp"

using tacticode::utils::Singleton;
using tacticode::utils::Configuration;

int main(int ac, char** av)
{	
	tacticode::engine::BattleEngine engine;

	auto conf = Singleton<Configuration>::GetInstance();
	conf->set("startup_path", std::string(av[0]));

	try
	{
		engine.readOnStdin();
	}
	catch (std::exception e) // catch parsing errors
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	if (engine.isReady())
	{
		engine.game();
	}
	return EXIT_SUCCESS;
}
