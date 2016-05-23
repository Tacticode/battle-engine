#include "tacticode/file/IValue.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"

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
			if (!json.hasField("map"))
			{
				throw file::error::InvalidConfiguration("root", "No map field");
			}
			m_map = std::make_shared<Map>(*json["map"]);
			if (!json.hasField("teams"))
			{
				throw file::error::InvalidConfiguration("root", "No teams field");
			}
			if (!json["teams"]->isArray())
			{
				throw file::error::InvalidConfiguration("root", "teams field is not an array");
			}
			auto & teams = *json["teams"];
			for (size_t i = 0; i < teams.size(); ++i) // no std::array :(
			{
				m_teams.push_back(std::make_shared<Team>(*teams[i]));
			}

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