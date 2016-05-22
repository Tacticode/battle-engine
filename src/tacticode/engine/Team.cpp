#include "Team.hpp"
#include "Character.hpp"

namespace tacticode
{
	namespace engine
	{
		void Team::deserialize(file::IValue & json)
		{
			// TODO: deserilize team infos
			// foreach character, deserialize
		}

		Team::Team(file::IValue& json)
		{
		}

		std::list<std::shared_ptr<Character>>& Team::getCharacters()
		{
			return m_characters;
		}

		const std::list<std::shared_ptr<Character>>& Team::getCharacters() const
		{
			return m_characters;
		}
	}
}