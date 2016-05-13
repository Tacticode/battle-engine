#pragma once

#include <vector>
#include <memory>

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
			struct Attributes {
				size_t       attack;
				size_t       power;
				size_t       defense;
				size_t       resilience;
				size_t       luck;
				size_t       health;
			};

		private:
			size_t m_currentHealth;
			const Attributes m_baseAttributes; // Those attributes can be used by buff to make calculations
			Attributes m_currentAttributes; // Those attributes are used in combat
			std::vector<std::shared_ptr<effect::IEffect>> m_effects;
			std::vector<std::shared_ptr<spell::ISpell>> m_spells;
			std::string m_script;

		public:
			explicit Character(Attributes& baseAttributes);

			void applyEffects();
			void play();
			void executeScript();

			void setScript(const std::string & script);
			void addEffect(std::shared_ptr<effect::IEffect> effect);
		};

	}
}
