#include "LineAoeEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		LineAoeEffect::LineAoeEffect(size_t aoe)
			: m_aoe(aoe)
		{
		}
		void	LineAoeEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell)
		{
			int los = 1;
			if (los == true)
			{
				std::list<std::shared_ptr<engine::Character> > targets;
				for (size_t i = 0; i < m_aoe; ++i)
				{
					if (cell->getCharacter())
				}
				// if (target)
				//	target->applyDamage(spell.getPower() * caster->m_currentAttributes->power / target->m_currentAttributes->resilience);
			}
		}
	}
}
