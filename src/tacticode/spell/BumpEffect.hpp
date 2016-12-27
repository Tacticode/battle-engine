#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class BumpEffect : public IEffect
		{
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			BumpEffect(std::shared_ptr<IEffect> effects);
			virtual ~BumpEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);
			virtual void applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine){}
		};
	}
}
