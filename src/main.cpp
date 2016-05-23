#include <iostream>
#include <cstdlib>
#include "tacticode/engine/BattleEngine.hpp"

int main(int, char*[])
{
	tacticode::engine::BattleEngine engine;
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
