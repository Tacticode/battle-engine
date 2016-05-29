#include "Character.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "tacticode/spell/ISpell.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"

namespace tacticode
{
	namespace engine
	{

		const std::array<std::string, 4> Character::validBreeds =
			{ "elf", "gobelin", "human", "orc" };
		const std::array<std::string, 8> Character::validAttributes =
			{ "health", "attack", "power", "defense", "resilience", "luck", "movement", "speed" };

		// no braces initialization with make_unique
		Character::Attributes::Attributes(
			size_t health_, size_t attack_, size_t power_,
			size_t defense_, size_t resilience_, size_t luck_,
			size_t movement_, size_t speed_)
			:
			health(health_), attack(attack_), power(power_),
			defense(defense_), resilience(resilience_),
			luck(luck_), movement(movement_), speed(speed_)
		{
		}

		Character::Character(const file::IValue& json)
		{
			deserialize(json);
		}

		void Character::assertAttributeDeserialize(const file::IValue& json, std::string attribute)
		{
			if (!json.hasField(attribute))
			{
				throw file::error::InvalidConfiguration("character", "character has no " + attribute);
			}
			if (!json[attribute]->isNumeric())
			{
				throw file::error::InvalidConfiguration("character", attribute + " field is not a string");
			}
			if (json[attribute]->asInt() < 0)
			{
				throw file::error::InvalidConfiguration("character", attribute + " cannot be less than 0");
			}
		}

		void Character::deserializeAttributes(const file::IValue& json)
		{
			for (auto & e : validAttributes)
			{
				assertAttributeDeserialize(json, e);
			}
			if (json["health"]->asInt() == 0)
			{
				throw file::error::InvalidConfiguration("character", "health must be greater than 0");
			}
			m_baseAttributes = std::make_unique<Attributes>(
				static_cast<size_t>(json["health"]->asInt()),
				static_cast<size_t>(json["attack"]->asInt()),
				static_cast<size_t>(json["power"]->asInt()),
				static_cast<size_t>(json["defense"]->asInt()),
				static_cast<size_t>(json["resilience"]->asInt()),
				static_cast<size_t>(json["luck"]->asInt()),
				static_cast<size_t>(json["movement"]->asInt()),
				static_cast<size_t>(json["speed"]->asInt())
			);
			m_currentAttributes = std::make_unique<Attributes>(*m_baseAttributes);
			m_currentHealth = m_baseAttributes->health;
		}

		void Character::deserialize(const file::IValue& json)
		{
			if (!json.isObject())
			{
				throw file::error::InvalidConfiguration("character", "item of characters field is not an object");
			}
			if (!json.hasField("name"))
			{
				throw file::error::InvalidConfiguration("character", "character has no name");
			}
			if (!json["name"]->isString())
			{
				throw file::error::InvalidConfiguration("character", "name field is not a string");
			}
			m_name = json["name"]->asString();
			if (!json.hasField("breed"))
			{
				throw file::error::InvalidConfiguration("character", "character has no breed");
			}
			if (!json["breed"]->isString())
			{
				throw file::error::InvalidConfiguration("character", "breed field is not a string");
			}
			const std::string & breed = json["breed"]->asString();
			if (!isValidBreed(breed))
			{
				throw file::error::InvalidConfiguration("character", "breed (" + breed + ") is not a valid string");
			}
			m_breed = stringToBreed(breed);
			if (!json.hasField("spells"))
			{
				throw file::error::InvalidConfiguration("character", "character has no spells field");
			}
			if (!json["spells"]->isArray())
			{
				throw file::error::InvalidConfiguration("character", "spells field is not an array");
			}
			const auto & spells = *json["spells"];
			for (size_t i = 0; i < spells.size(); ++i)
			{
				if (!spells[i]->isString())
				{
					throw file::error::InvalidConfiguration("character", "item of spells is not a string");
				}
				addSpell(spells[i]->asString());
			}
			deserializeAttributes(json);
		}

		void Character::addSpell(const std::string & spellName) // TODO: Wilko
		{
			// this should throw an exception if the spellName does not exist: tacticode::spell::error::InvalidSpellName()
			//std::unique_ptr<spell::ISpell> ptr = spellFactory().createSpell(spellName);
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
			for (auto & effect : m_effects)
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

		void Character::addEffect(std::unique_ptr<effect::IEffect> effect)
		{
			m_effects.push_back(std::move(effect));
		}

		//todo : prevoir cas spéciaux si besoin
		void Character::applyDamage(size_t damages)
		{
			m_currentAttributes->health -= damages;
		}
		void Character::applyHeal(size_t heal)
		{
			m_currentAttributes->health += heal;
		}
	}
}
