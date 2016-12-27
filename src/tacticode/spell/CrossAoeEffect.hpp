#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class CrossAoeEffect : public IEffect
		{
			size_t m_aoe;
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			CrossAoeEffect(size_t aoe, std::shared_ptr<IEffect> effects);
			virtual ~CrossAoeEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);
				virtual void applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine){}
		};
	}
}
