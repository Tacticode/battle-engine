#include "tacticode/file/error/InvalidConfiguration.hpp"
#include "Team.hpp"
#include "Character.hpp"

namespace tacticode
{
	namespace engine
	{
		void Team::deserialize(const file::IValue& json)
		{
			// TODO: deserilize team infos
			// foreach character, deserialize
			if (!json.isObject())
			{
				throw file::error::InvalidConfiguration("teams", "array child is not an object");
			}
			if (!json["name"])
			{
				throw file::error::InvalidConfiguration("teams", "team has no name");
			}
			if (!json["name"]->isString())
			{
				throw file::error::InvalidConfiguration("teams", "name field is not a string");
			}
			m_name = json["name"]->asString();
			if (!json["id"])
			{
				throw file::error::InvalidConfiguration("teams", "team has no id");
			}
			if (!json["id"]->isNumeric() || json["id"]->asInt() < 0)
			{
				throw file::error::InvalidConfiguration("teams", "id field is not a positive number");
			}
			m_id = json["id"]->asInt();
		}

		Team::Team(const file::IValue& json)
		{
			deserialize(json);
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