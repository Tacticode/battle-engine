#include "tacticode/file/IValue.hpp"
#include "tacticode/file/JsonLoader.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"

#include "BattleEngine.hpp"
#include "Team.hpp"
#include "Character.hpp"
#include "Map.hpp"

#include "tacticode/utils/utils.hpp"

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
			auto teams = json["teams"];
			for (size_t i = 0; i < teams->size(); ++i) // no std::array :(
			{
				auto currentTeam = (*teams)[i];
				m_teams.push_back(std::make_shared<Team>(*currentTeam, m_map));
			}

			for (auto & t : m_teams)
			{
				for (auto & c : t->getCharacters())
				{
					const Vector2i & position = c->getPosition();
					if (!m_map->isCellOnMap(position.x, position.y))
					{
						throw file::error::InvalidConfiguration("root", "character " + c->getName() + " has an invalid position");
					}
					auto & cell = m_map->getCell(position);
					if (!cell.isFree())
					{
						//throw file::error::InvalidConfiguration("root", "character tried to access an already taken cell: " + c->getName());
					}
					if (!cell.isAccessible())
					{
						throw file::error::InvalidConfiguration("root", "character position target a non accessible cell: " + c->getName());
					}
					cell.setCharacterId(c->getId());
					m_characters.push_back(c);
					utils::Singleton<utils::FightLogger>::GetInstance()->addEntity(
						utils::Log::Entity(c->getId(), position.x, position.y, c->getBreedString(), t->m_id));
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
				BattleEngineContext context;

				context.team = NULL; //todo
				context.character = &(*character);

				character->play(context);
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
		std::shared_ptr<Map> BattleEngine::getMap()
		{
			return (m_map);
		}
		std::shared_ptr<Character> BattleEngine::getCharacter(int32_t characterId)
		{
			for (int i = 0; i < m_characters.size(); ++i)
			{
				if (m_characters[i]->getId() == characterId)
					return (m_characters[i]);
			}
			return (nullptr);
		}
	}
}
