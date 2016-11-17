#include "Character.hpp"
#include "Map.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "tacticode/spell/ISpell.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"
#include "tacticode/utils/utils.hpp"
#include "ICharacterScript.hpp"
#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/spell/SpellFactory.hpp"
#include "tacticode/utils/utils.hpp"
#include <cstring>
#include <algorithm>

namespace tacticode
{
	namespace engine
	{

		const std::array<std::string, 4> Character::validBreeds =
			{ "elf", "goblin", "human", "orc" };
		const std::array<std::string, 8> Character::validAttributes =
			{ "health", "attack", "power", "defense", "resilience", "luck", "movement", "speed" };

		// no braces initialization with make_unique
		Character::Attributes::Attributes(
			int32_t health_, int32_t attack_, int32_t power_,
			int32_t defense_, int32_t resilience_, int32_t luck_,
			int32_t movement_, int32_t speed_)
			:
			health(health_), attack(attack_), power(power_),
			defense(defense_), resilience(resilience_),
			luck(luck_), movement(movement_), speed(speed_)
		{
		}

		std::string const& Character::getBreedString() const{
			return validBreeds[getBreed()];
		}

		Character::Character(const file::IValue& json, std::shared_ptr<Map> map, int32_t teamId)
			: m_map(map)
		{
			#ifdef V8LINK
			m_script = utils::Singleton<script::ScriptFactory>::GetInstance()->newCharacterScript();
			#endif
			deserialize(json);
			m_teamId = teamId;
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
				static_cast<int32_t>(json["health"]->asInt()),
				static_cast<int32_t>(json["attack"]->asInt()),
				static_cast<int32_t>(json["power"]->asInt()),
				static_cast<int32_t>(json["defense"]->asInt()),
				static_cast<int32_t>(json["resilience"]->asInt()),
				static_cast<int32_t>(json["luck"]->asInt()),
				static_cast<int32_t>(json["movement"]->asInt()),
				static_cast<int32_t>(json["speed"]->asInt())
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
			if (!json.hasField("id"))
			{
				throw file::error::InvalidConfiguration("character", "character has no id");
			}
			if (!json["id"]->isNumeric())
			{
				throw file::error::InvalidConfiguration("character", "id field is not a number");
			}
			m_id = json["id"]->asInt();
			if (!json.hasField("breed"))
			{
				throw file::error::InvalidConfiguration("character", "character has no breed");
			}
			if (!json["breed"]->isString())
			{
				throw file::error::InvalidConfiguration("character", "breed field is not a string");
			}
			std::string breed = json["breed"]->asString();
			std::transform(breed.begin(), breed.end(), breed.begin(), ::tolower);
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
			auto spells = json["spells"];
			for (size_t i = 0; i < spells->size(); ++i)
			{
				if (!(*spells)[i]->isString())
				{
					throw file::error::InvalidConfiguration("character", "item of spells is not a string");
				}
				const auto spellName = (*spells)[i]->asString();
				if (m_spells.find(spellName) != m_spells.end())
				{
					throw file::error::InvalidConfiguration("character", "a spell name is defined more than one time");
				}
				addSpell(spellName);
			}
			deserializeAttributes(json);
			if (m_script != nullptr)
			{
				setScript(json.getString("script", std::string("$log('unset") + __FILE__ + "': )"));
			}
		}

		void Character::addSpell(const std::string & spellName)
		{
			m_spells[spellName] = 0;
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

		bool Character::isDead() const
		{
			return getCurrentHealth() <= 0;
		}

		void Character::play(BattleEngineContext& context)
		{
			if (m_currentHealth <= 0)
			{
				return;
			}
			m_cooldown.movement = m_currentAttributes->movement;
			m_cooldown.spell = false;
			applyEffects();
			executeScript(context);
		}

		void Character::executeScript(BattleEngineContext& context)
		{
			// TODO
			if (m_script != nullptr)
			{
				BattleEngineContext *script_context = m_script->getBattleEngineContext();
				script_context->character = context.character;
				script_context->team = context.team;
				script_context->engine = context.engine;

				m_script->run();
			}
		}

		void Character::setScript(const std::string & script)
		{
			m_script->setScript(script);
		}

		const std::shared_ptr<ICharacterScript> & Character::getScript() const
		{
			return m_script;
		}

		Character::Attributes & Character::getCurrentAttributes()
		{
			return *m_currentAttributes;
		}

		const Character::Attributes & Character::getCurrentAttributes() const
		{
			return *m_currentAttributes;
		}

		const std::string & Character::getName() const
		{
			return m_name;
		}

		Character::Breed Character::getBreed() const
		{
			return m_breed;
		}

		int32_t Character::getCurrentHealth() const
		{
			return m_currentHealth;
		}

		const Character::Attributes & Character::getBaseAttributes() const
		{
			return *m_baseAttributes;
		}

		int32_t Character::getId() const
		{
			return m_id;
		}

		int32_t Character::getTeamId() const
		{
			return m_teamId;
		}

		bool Character::getCooldownSpell() const
		{
			return m_cooldown.spell;
		}

		int32_t Character::getCurrentMovementPoints() const
		{
			return m_cooldown.movement;
		}

		void Character::reduceCurrentMovementPoint(int32_t reductor)
		{
			m_cooldown.movement -= reductor;
			if (m_cooldown.movement < 0)
			{
				m_cooldown.movement = 0;
			}
		}

		const std::vector<std::unique_ptr<effect::IEffect>>& Character::getEffects() const
		{
			return m_effects;
		}

		bool Character::hasSpell(const std::string & name) const
		{
			return m_spells.find(name) != m_spells.end();
		}

		spell::ISpell & Character::getSpellByName(const std::string & spellName)
		{
			auto spellFactory = utils::Singleton<spell::SpellFactory>::GetInstance();
			return *spellFactory->get(spellName);
		}

		int32_t Character::getSpellCooldown(const std::string & spellName) const
		{
			const auto & it = m_spells.find(spellName);
			if (it == m_spells.end())
			{
				return -1;
			}
			return it->second;
		}

		const std::unique_ptr<std::list<std::string>> Character::getSpells() const
		{
			auto spellNames = std::make_unique<std::list<std::string>>();
			for (auto & item : m_spells)
			{
				spellNames->emplace_back(item.first);
			}
			return spellNames;
		}

		const Vector2i & Character::getPosition() const
		{
			return m_position;
		}

		void Character::setPosition(int x, int y)
		{
			m_position.x = x;
			m_position.y = y;
		}

		void Character::setPosition(const Vector2i & position)
		{
			m_position = position;
		}

		void Character::addEffect(std::unique_ptr<effect::IEffect> effect)
		{
			m_effects.push_back(std::move(effect));
		}

		bool Character::moveToCell(const Vector2i & position)
		{
			if (m_map->moveCharacterToCell(*this, position))
			{
				auto action = utils::Log::Action(m_id, position.x, position.y, "move");
				utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
				return true;
			}
			return false;
		}

		bool Character::castSpell(std::string const & spellName,
			const Vector2i & position,
			BattleEngine & engine)
		{
			if (!hasSpell(spellName) || !m_map->isCellOnMap(position))
			{
				return false;
			}
			auto & spell = getSpellByName(spellName);

			// auto action = utils::Log::Action(m_id, position.x, position.y, "skill");
			// action.add("skill", spellName);
			// utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);

			// if (spell.getLos() && engine.getMap()->hasCellLineOfSightOnCell(getPosition().x, getPosition().y, position.x, position.y))
			// {
			// 	action.add("skill", "spell failed (LoS)");
			// 	return false;
			// }

			spell.castSpell(m_id, m_map->getManagedCell(position.x, position.y), engine);
			return true;
		}

		//todo : prevoir cas spéciaux si besoin
		void Character::applyDamage(int32_t damages)
		{
			auto action = utils::Log::Action(m_id, "damage");
			action.add("health", damages);
			utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);

			if (!isDead()) {
				// TODO: what's the difference?
				m_currentHealth -= damages;
				m_currentAttributes->health -= damages;
				if (isDead()) {
					auto action = utils::Log::Action(m_id, "death");
					utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
					m_map->getCell(m_position.x, m_position.y).unsetCharacterId();
				}
			}
		}

		void Character::applyHeal(int32_t heal)
		{
			if (!isDead()) {
				// TODO: what's the difference?
				m_currentHealth += heal;
				m_currentAttributes->health += heal;

				auto action = utils::Log::Action(m_id, "heal");
				action.add("health", heal);
				utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
			}
		}
		void Character::addBuff(std::shared_ptr<spell::ISpell> buff)
		{
			m_buff.push_back(buff);
		}
		void Character::removeBuff()
		{
			for (std::list<std::shared_ptr<spell::ISpell>>::iterator it = m_buff.begin(); it != m_buff.end();++it)
			{
				//if ((*it)->time <= 0)
				//{
					//pop list;
				//}
			}
		}
		void Character::applyBuff()
		{
			// for (std::list<std::shared_ptr<spell::ISpell>>::iterator it = m_buff.begin(); it != m_buff.end();++it)
			// {
			// 	for (std::list<std::shared_ptr<spell::IEffect>>::const_iterator it2 = (*it)->getEffects().begin(); it2 != (*it)->getEffects().end(); ++it2)
			// 	{

			// 	}
			// }
		}
	}
}
