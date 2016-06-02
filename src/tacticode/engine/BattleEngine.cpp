#include "tacticode/file/IValue.hpp"
#include "tacticode/file/JsonLoader.hpp"
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

		void BattleEngine::deserialize(const file::IValue& json)
		{
			// TODO
			if (!json.hasField("map"))
			{
				throw file::error::InvalidConfiguration("root", "No map field");
			}
			auto _map = json["map"];
			m_map = std::make_shared<Map>(*_map);
			if (!json.hasField("teams"))
			{
				throw file::error::InvalidConfiguration("root", "No teams field");
			}
			if (!json["teams"]->isArray())
			{
				throw file::error::InvalidConfiguration("root", "teams field is not an array");
			}
			auto _teams = json["teams"];
			auto & teams = *_teams;
			for (size_t i = 0; i < teams.size(); ++i) // no std::array :(
			{
				auto _teams_i = teams[i];
				m_teams.push_back(std::make_shared<Team>(*_teams_i));
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
			file::JsonLoader input(std::cin);

			deserialize(input.value());
		}

		bool BattleEngine::isReady()
		{
			return true;
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
			int i = 0;
			while (round() && i < 10)
				++i;
			//TODO: use datas created by gameOver();
		}
	}
}