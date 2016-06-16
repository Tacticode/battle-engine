#pragma once

#include <list>

#include "tacticode/file/IValue.hpp"

namespace tacticode
{
	namespace engine
	{
		class Map;
		class Character;

		class Team
		{
			size_t m_id;
			std::string m_name;
			std::list<std::shared_ptr<Character>> m_characters;
			std::shared_ptr<Map> m_map;

			void deserialize(const file::IValue& json);

		public:
			explicit Team(const file::IValue& json, std::shared_ptr<Map> map);

			const std::list<std::shared_ptr<Character>>& getCharacters() const;
			std::list<std::shared_ptr<Character>>& getCharacters();
		};
	}
}