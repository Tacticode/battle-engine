#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class BuffEffect : public IEffect
		{
			size_t m_aoe;
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			BuffEffect(std::shared_ptr<IEffect> effects);
			virtual ~BuffEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);
		};
	}
}
