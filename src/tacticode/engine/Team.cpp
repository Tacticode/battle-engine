#include "tacticode/file/error/InvalidConfiguration.hpp"
#include "Team.hpp"
#include "Character.hpp"

#include <iostream>
using std::cerr;
using std::endl;
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
			if (!json.hasField("name"))
			{
				throw file::error::InvalidConfiguration("teams", "team has no name");
			}
			if (!json["name"]->isString())
			{
				throw file::error::InvalidConfiguration("teams", "name field is not a string");
			}
			m_name = json["name"]->asString();
			if (!json.hasField("id"))
			{
				throw file::error::InvalidConfiguration("teams", "team has no id");
			}
			if (!json["id"]->isNumeric() || json["id"]->asInt() < 0)
			{
				throw file::error::InvalidConfiguration("teams", "id field is not a positive number");
			}
			m_id = json["id"]->asInt();
			if (!json.hasField("characters"))
			{
				throw file::error::InvalidConfiguration("teams", "team has no characters");
			}
			if (!json["characters"]->isArray())
			{
				throw file::error::InvalidConfiguration("teams", "characters field is not an array");
			}
			auto _characters = json["characters"];
			auto & characters = *_characters;
			for (size_t i = 0; i < characters.size(); ++i)
			{
				auto _characters_i = characters[i];
				auto & character = *_characters_i;
				m_characters.push_back(std::make_shared<Character>(character));
			}
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