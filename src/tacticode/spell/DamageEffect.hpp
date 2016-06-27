#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class DamageEffect : public IEffect
		{
		public:
			DamageEffect();
			virtual ~DamageEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);
		};
	}
}
