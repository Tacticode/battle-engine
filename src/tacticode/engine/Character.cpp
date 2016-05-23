#include "Character.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "tacticode/spell/ISpell.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"

namespace tacticode
{
	namespace engine
	{

		const std::array<std::string, 4> Character::validBreeds = { "elf", "gobelin", "human", "orc" };

		Character::Character(const file::IValue& json) : m_baseAttributes()
		{
			deserialize(json);
		}

		void Character::deserialize(const file::IValue& json)
		{
			if (!json.isObject())
			{
				throw file::error::InvalidConfiguration("character", "item of characters field is not an object");
			}
			if (!json.hasField("breed"))
			{
				throw file::error::InvalidConfiguration("character", "character has no breed");
			}
			if (!json["breed"]->isString())
			{
				throw file::error::InvalidConfiguration("character", "breed field is not a string");
			}
			std::string & breed = json["breed"]->asString();
			if (!isValidBreed(breed))
			{
				throw file::error::InvalidConfiguration("character", "breed (" + breed + ") is not a valid string");
			}
			m_breed = stringToBreed(breed);
		}


		Character::Breed Character::stringToBreed(const std::string & breed)
		{
			for (size_t i = 0; i < validBreeds.size(); ++i)
			{
				if (breed == validBreeds[i])
				{
					return static_cast<Breed>(i);
				}
			}
			throw std::runtime_error("tried to convert an invalid breed string");
		}

		bool Character::isValidBreed(const std::string & breed)
		{
			for (auto & e : validBreeds)
			{
				if (breed == e)
				{
					return true;
				}
			}
			return false;
		}

		void Character::applyEffects()
		{
			for (auto effect : m_effects)
			{
				effect->apply(*this);
			}
		}

		void Character::play()
		{
			applyEffects();
			executeScript();
		}

		void Character::executeScript()
		{
			// TODO
		}

		void Character::setScript(const std::string & script)
		{
			m_script = script;
		}

		const std::string& Character::getScript() const
		{
			return m_script;
		}

		size_t Character::getTeamId() const
		{
			return m_teamId;
		}

		void Character::addEffect(std::shared_ptr<effect::IEffect> effect)
		{
			m_effects.push_back(effect);
		}
	}
}