#pragma once

#include <vector>
#include <memory>
#include <array>

#include "tacticode/file/IValue.hpp"

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
		class Character
		{
		public:
			struct Attributes
			{
				size_t attack;
				size_t power;
				size_t defense;
				size_t resilience;
				size_t luck;
				size_t health;
				size_t speed;
			};

			enum Breed
			{
				elf     = 0,
				gobelin = 1,
				human   = 2,
				orc     = 3
			};

			static const std::array<std::string, 4> validBreeds;

		private:
			std::string      m_name;
			Breed            m_breed;
			size_t           m_currentHealth;
			const Attributes m_baseAttributes;    // Those attributes can be used by buff to make calculations
			Attributes       m_currentAttributes; // Those attributes are used in combat
			size_t           m_teamId;
			std::vector<std::shared_ptr<effect::IEffect>> m_effects;
			std::vector<std::shared_ptr<spell::ISpell>>   m_spells;
			std::string m_script;

		public:
			explicit Character(const file::IValue& json);

			void deserialize(const file::IValue& json); // TODO
			void applyEffects(); // TODO
			void play();
			void executeScript(); // TODO

			bool isValidBreed(const std::string & breed);
			Breed stringToBreed(const std::string & breed);

			void setScript(const std::string & script);
			const std::string& getScript() const;
			size_t getTeamId() const;

			void addEffect(std::shared_ptr<effect::IEffect> effect);
		};

	}
}
