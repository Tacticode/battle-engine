#include <iostream>
#include <cstdlib>
#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/utils/utils.hpp"

using tacticode::utils::Singleton;
using tacticode::utils::Configuration;
using tacticode::script::ScriptFactory;
#include "v8.h"
#include <iostream>
int main(int ac, char** av)
{	
	tacticode::engine::BattleEngine engine;

	auto conf = Singleton<Configuration>::GetInstance();
	std::cerr << av[0] << std::endl;
	conf->set("startup_path", std::string(av[0]));
	auto scFact = Singleton<ScriptFactory>::GetInstance();

	v8::HandleScope scope(v8::Isolate::GetCurrent());
	try
	{
		engine.readOnStdin();
	}
	catch (std::exception &e) // catch parsing errors
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
