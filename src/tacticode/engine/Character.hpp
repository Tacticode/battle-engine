#pragma once

#include <vector>
#include <memory>
#include <map>
#include <array>

#include "tacticode/file/IValue.hpp"
#include "tacticode/spell/Spell.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "ICharacterScript.hpp"

namespace tacticode
{
	namespace effect
	{
		class IEffect; // buff, debuff, poison (cast a spell), heal (cast a spell) etc...
	}
	namespace spell
	{
		class ISpell;
	}
	namespace engine
	{
		class Map;

		class Character
		{
		public:
			struct Attributes
			{
				int32_t health;
				int32_t attack;
				int32_t power;
				int32_t defense;
				int32_t resilience;
				int32_t luck;
				int32_t movement;
				int32_t speed;
				Attributes(
					int32_t health_, int32_t attack_, int32_t power_,
					int32_t defense_, int32_t resilience_, int32_t luck_,
					int32_t movement_, int32_t speed_);
			};

			enum Breed
			{
				elf		= 0,
				goblin  = 1,
				human	= 2,
				orc		= 3
			};

			struct Cooldown
			{
				int32_t movement;
				bool spell;
			};

		private:
			Vector2i                          m_position;
			std::unique_ptr<Attributes>		  m_currentAttributes; // Those attributes are used in combat
			std::string						  m_name;
			Breed							  m_breed;
			int32_t							  m_currentHealth;
			std::unique_ptr<const Attributes> m_baseAttributes;	   // Those attributes can be used by buff to make calculations

			int32_t                           m_id;
			int32_t							  m_teamId;
			std::shared_ptr<Map>              m_map;
			Cooldown                          m_cooldown;

			std::vector<std::unique_ptr<effect::IEffect>> m_effects;
			std::map<std::string, int32_t>	              m_spells;
			std::shared_ptr<ICharacterScript>             m_script;

		public:
			static const std::array<std::string, 4> validBreeds;
			static const std::array<std::string, 8> validAttributes;

			explicit Character(const file::IValue& json, std::shared_ptr<Map> map, int32_t teamId);
			std::string const& getBreedString() const;

			void deserialize(const file::IValue& json);
			void deserializeAttributes(const file::IValue& json);
			void assertAttributeDeserialize(const file::IValue& json, std::string attribute);

			void applyEffects(); // TODO
			void applyDamage(int32_t damages);
			void applyHeal(int32_t heal);
			void play(BattleEngineContext& );
			void executeScript(BattleEngineContext& ); // TODO

			bool isValidBreed(const std::string & breed);
			Breed stringToBreed(const std::string & breed);

			void setScript(const std::string & script);
			const std::shared_ptr<ICharacterScript> & getScript() const;

			Attributes &        getCurrentAttributes();
			const Attributes &  getCurrentAttributes()     const;
			const std::string & getName()                  const;
			Breed               getBreed()                 const;
			int32_t	            getCurrentHealth()         const;
			const Attributes &  getBaseAttributes()        const;
			int32_t             getId()                    const;
			int32_t             getTeamId()                const;
			bool			    getCooldownSpell()         const;
			int32_t             getCurrentMovementPoints() const;

			void reduceCurrentMovementPoint(int32_t reductor);

			const std::vector<std::unique_ptr<effect::IEffect>> & getEffects() const;

			bool hasSpell(const std::string & name) const;
			const spell::ISpell & getSpellByName(const std::string & spellName) const;
			int32_t getSpellCooldown(const std::string & spellName) const;
			const std::unique_ptr<std::list<std::string>> getSpells() const;

			const Vector2i & getPosition() const;
			void setPosition(int x, int y);
			void setPosition(const Vector2i & position);

			void addSpell(const std::string & spellName); // TODO: Wilko
			void addEffect(std::unique_ptr<effect::IEffect> effect);

			bool moveToCell(const Vector2i & position);
			bool launchSpell(std::string const&, int x, int y);
		};

	}
}
