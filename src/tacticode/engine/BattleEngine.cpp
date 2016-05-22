#include "tacticode\file\IValue.hpp"

#include "BattleEngine.hpp"
#include "Team.hpp"
#include "Character.hpp"
#include "Map.hpp"

namespace tacticode
{
	namespace engine
	{
		BattleEngine::BattleEngine()
		{
		}

		void BattleEngine::deserialize(file::IValue& json)
		{
			// TODO
			// map = std::make_shared<Map>(/* jMap */);
			for (auto & t : m_teams)
			{
				for (auto & c : t->getCharacters())
				{
					m_characters.push_back(c);
				}
			}
		}

		void BattleEngine::readOnStdin()
		{
			// TODO: get json on stdin
			//loadJson(json);
		}

		bool BattleEngine::isReady()
		{
			return false;
		}

		bool BattleEngine::round()
		{
			for (auto& character : m_characters)
			{
				character->play();
				if (gameOver())
				{
					return false;
				}
			}
			return true;
		}

		bool BattleEngine::gameOver()
		{
			return false;
		}

		void BattleEngine::game()
		{
			while (round());
			//TODO: use datas created by gameOver();
		}
	}
}