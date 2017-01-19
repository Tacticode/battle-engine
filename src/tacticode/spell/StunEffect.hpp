#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class StunEffect : public IEffect
		{
		public:
			StunEffect();
			virtual ~StunEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);
				virtual void applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine){}
		};
	}
}
