#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class BuffEffect : public IEffect
		{
			size_t m_aoe;
			size_t m_nbTurn;
			std::list<std::shared_ptr<IEffect>> m_effects;
			std::shared_ptr<Spell> m_spell;
		public:
			BuffEffect(size_t nbTurn, std::shared_ptr<IEffect> effects);
			virtual ~BuffEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1);

			virtual void applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine);
		};
	}
}
