#pragma once

#include <vector>
#include <memory>

namespace tacticode
{
	namespace file
	{
		class IValue;
	}

	namespace engine
	{
		class Character;

		class BattleEngine
		{
		private:
			bool isGameOver;
			std::vector<std::shared_ptr<Character>> characters;

		public:
			BattleEngine();

			void loadJson(file::IValue& json);
			void readOnStdin(); //TODO: read the JSON on standard input
			bool isReady(); //TODO: is engine ready to start a game?
			void game();
			bool round();
			bool gameOver(); //TODO set gameOver datas and return true, if game is over
		};
	}
}