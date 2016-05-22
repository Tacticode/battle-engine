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
		class Map;
		class Team;

		class BattleEngine
		{
		private:
			bool m_isGameOver;
			std::vector<std::shared_ptr<Team>>      m_teams;
			std::vector<std::shared_ptr<Character>> m_characters;
			std::shared_ptr<Map>                    m_map;

		public:
			explicit BattleEngine();

			void deserialize(file::IValue& json);
			void readOnStdin(); //TODO: read the JSON on standard input
			bool isReady(); //TODO: is engine ready to start a game?
			void game();
			bool round();
			bool gameOver(); //TODO set gameOver datas and return true, if game is over
		};
	}
}