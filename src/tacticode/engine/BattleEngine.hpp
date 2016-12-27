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
			const int TURN_LIMIT = 100;

			bool m_isGameOver;
			std::vector<std::shared_ptr<Team> >		 m_teams;
			std::vector<std::shared_ptr<Character> > m_characters;
			std::shared_ptr<Map>					m_map;
			int32_t winnerId;

		public:
			explicit BattleEngine();

			void deserialize(const file::IValue& json);
			void readOnStdin(); //TODO: read the JSON on standard input
			bool isReady(); //TODO: is engine ready to start a game?
			void game();
			bool round();
			bool gameOver(); //TODO set gameOver datas and return true, if game is over
			std::shared_ptr<Map> getMap();
			std::shared_ptr<Character> getCharacter(int32_t characterId);
			std::shared_ptr<Character> getCharacterOnCell(int32_t x, int32_t y);
			std::vector<std::shared_ptr<Character> >& getCharacters();
		};
	}
}
