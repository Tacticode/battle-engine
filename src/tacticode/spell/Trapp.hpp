#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class Trap
		{
			std::list<std::shared_ptr<IEffect> > m_effects;
			std::shared_ptr<engine::Cell> m_pos;
			std::shared_ptr<engine::Character> m_caster;
		public:
			Trap(engine::Cell cell, std::list<std::shared_ptr<IEffect> > effect, std::shared_ptr<engine::Character> caster, Spell spell);
			void applyEffect();
		};
	}
}
