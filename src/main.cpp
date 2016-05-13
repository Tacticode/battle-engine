#include "tacticode/engine/BattleEngine.hpp"

int main(int, char*[])
{
	tacticode::engine::BattleEngine engine;
	engine.readOnStdin();
	if (engine.isReady())
	{
		engine.game();
	}
}
