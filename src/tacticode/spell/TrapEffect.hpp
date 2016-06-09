#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class TrapEffect : public IEffect
		{
			std::list<std::shared_ptr<IEffect> > m_effects;
		public:
			TrapEffect(std::list<std::shared_ptr<IEffect> > effects);
			virtual ~TrapEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, Spell spell);
		};
	}
}
