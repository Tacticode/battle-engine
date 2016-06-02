#pragma once

#include <vector>
#include <memory>
#include <array>

#include "tacticode/file/IValue.hpp"
#include "tacticode/spell/ISpell.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "ICharacterScript.hpp"

namespace tacticode
{
	namespace effect
	{
		class IEffect; // buff, debuff, poison (cast a spell), heal (cast a spell) etc...
	}

	namespace engine
	{
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
				gobelin = 1,
				human	= 2,
				orc		= 3
			};

			static const std::array<std::string, 4> validBreeds;
			static const std::array<std::string, 8> validAttributes;

		private:
			std::string						  m_name;
			Breed							  m_breed;
			int32_t							  m_currentHealth;
			std::unique_ptr<const Attributes> m_baseAttributes;	   // Those attributes can be used by buff to make calculations
			std::unique_ptr<Attributes>		  m_currentAttributes; // Those attributes are used in combat
			int32_t							  m_teamId;

			std::vector<std::unique_ptr<effect::IEffect>> m_effects;
			std::vector<std::unique_ptr<spell::ISpell>>	  m_spells;
			std::string m_script;

			std::shared_ptr<ICharacterScript> _script;
		public:
			explicit Character(const file::IValue& json);

			void deserialize(const file::IValue& json);
			void deserializeAttributes(const file::IValue& json);
			void assertAttributeDeserialize(const file::IValue& json, std::string attribute);

			void applyEffects(); // TODO
			void applyDamage(int32_t damages);
			void applyHeal(int32_t heal);
			void play();
			void executeScript(); // TODO

			bool isValidBreed(const std::string & breed);
			Breed stringToBreed(const std::string & breed);

			void setScript(const std::string & script);
			const std::string& getScript() const;
			int32_t getTeamId() const;

			void addSpell(const std::string & spellName); // TODO: Wilko
			void addEffect(std::unique_ptr<effect::IEffect> effect);
		};

	}
}
