#pragma once

#include "IEffect.hpp"
#include "Trap.hpp"

namespace tacticode
{
	namespace spell
	{
		class Trap;
		class TrapEffect : public IEffect
		{
			std::list<std::shared_ptr<IEffect> > m_effects;
		public:
			TrapEffect(std::shared_ptr<IEffect>	 effects);
			virtual ~TrapEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell);
		};
	}
}
