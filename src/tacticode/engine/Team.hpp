#pragma once

#include <list>

#include "tacticode/file/IValue.hpp"

namespace tacticode
{
	namespace engine
	{
		class Character;

		class Team
		{
			size_t m_id;
			std::list<std::shared_ptr<Character>> m_characters;

			void deserialize(file::IValue& json);

		public:
			explicit Team(file::IValue& json);
			std::list<std::shared_ptr<Character>> getCharacters();
			std::list<std::shared_ptr<Character>> getCharacters() const;
		};
	}
}