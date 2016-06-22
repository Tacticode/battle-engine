#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class LineAoeEffect : public IEffect
		{
			size_t m_aoe;
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			LineAoeEffect(size_t aoe, std::shared_ptr<IEffect> effects);
			virtual ~LineAoeEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell);
		};
	}
}
