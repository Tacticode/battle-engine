#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class InvisibleEffect : public IEffect
		{
		public:
			InvisibleEffect();
			virtual ~InvisibleEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);
				virtual void applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine){}
		};
	}
}
