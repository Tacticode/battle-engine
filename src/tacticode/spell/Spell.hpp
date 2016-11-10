#pragma once

#include "ISpell.hpp"

namespace tacticode
{
	namespace spell
	{
		class IEffect;
		class Spell : public ISpell
		{
		protected:
			float m_power;
			size_t m_range;
			size_t m_aoe;
			size_t m_cooldown;
			size_t m_los;
			size_t m_isActive;
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			Spell(std::shared_ptr<IEffect> effect, std::string const& name, float power, size_t range, size_t cooldown, size_t active, size_t aoe, size_t los);
			virtual ~Spell() = default;
			void castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine);
			virtual const float getPower() const;
			virtual const size_t getRange() const;
			virtual const size_t getCooldown() const;
			virtual const size_t getIsActive() const;
			virtual const size_t getAoe() const;
			virtual const size_t getLos() const;
		};
	}
}
