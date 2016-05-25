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
				size_t health;
				size_t attack;
				size_t power;
				size_t defense;
				size_t resilience;
				size_t luck;
				size_t movement;
				size_t speed;
				Attributes(
					size_t health_, size_t attack_, size_t power_,
					size_t defense_, size_t resilience_, size_t luck_,
					size_t movement_, size_t speed_);
			};

			enum Breed
			{
				elf     = 0,
				gobelin = 1,
				human   = 2,
				orc     = 3
			};

			static const std::array<std::string, 4> validBreeds;
			static const std::array<std::string, 8> validAttributes;

		private:
			std::string                       m_name;
			Breed                             m_breed;
			size_t                            m_currentHealth;
			std::unique_ptr<const Attributes> m_baseAttributes;    // Those attributes can be used by buff to make calculations
			std::unique_ptr<Attributes>       m_currentAttributes; // Those attributes are used in combat
			size_t                            m_teamId;

			std::vector<std::unique_ptr<effect::IEffect>> m_effects;
			std::vector<std::unique_ptr<spell::ISpell>>   m_spells;
			std::string m_script;

		public:
			explicit Character(const file::IValue& json);

			void deserialize(const file::IValue& json);
			void deserializeAttributes(const file::IValue& json);
			void assertAttributeDeserialize(const file::IValue& json, std::string attribute);

			void applyEffects(); // TODO
			void play();
			void executeScript(); // TODO

			bool isValidBreed(const std::string & breed);
			Breed stringToBreed(const std::string & breed);

			void setScript(const std::string & script);
			const std::string& getScript() const;
			size_t getTeamId() const;

			void addSpell(const std::string & spellName); // TODO: Wilko
			void addEffect(std::shared_ptr<effect::IEffect> effect);
		};

	}
}
