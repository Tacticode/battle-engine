#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class LineAoeEffect : public IEffect
		{
			size_t m_aoe;
		public:
			LineAoeEffect(size_t aoe);
			virtual ~LineAoeEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, Spell spell);
		};
	}
}
