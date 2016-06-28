#include <iostream>
#include <cstdlib>
#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/utils/utils.hpp"
#include "tacticode/spell/SpellFactory.hpp"

using tacticode::utils::Singleton;
using tacticode::utils::Configuration;
using tacticode::script::ScriptFactory;
using tacticode::utils::FightLogger;
using tacticode::spell::SpellFactory;

#include <iostream>
#include <ctime>

int main(int ac, char** av)
{	
	std::srand(std::time(0));
	tacticode::engine::BattleEngine engine;

	auto conf = Singleton<Configuration>::GetInstance();
	std::cerr << av[0] << std::endl;
	conf->set("startup_path", std::string(av[0]));
	auto scFact = Singleton<ScriptFactory>::GetInstance();
	auto spFact = Singleton<SpellFactory>::GetInstance();

	spFact->init();

	#ifdef V8LINK	
	v8::HandleScope scope(v8::Isolate::GetCurrent());
	#endif

	//instatiate logger
	auto logger = Singleton<FightLogger>::GetInstance();
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

	Singleton<FightLogger>::Destroy();
	Singleton<SpellFactory>::Destroy();
	Singleton<ScriptFactory>::Destroy();
	Singleton<Configuration>::Destroy();
	return EXIT_SUCCESS;
}
