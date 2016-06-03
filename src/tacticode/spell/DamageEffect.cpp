#include "DamageEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		DamageEffect::DamageEffect()
		{

		}
//add context as parameter
		void	DamageEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, Spell spell)
		{
			int los = 1;
			if (los == true)
			{
				std::shared_ptr<engine::Character> target = nullptr; //==cell.getEntity()
				if (target)
					target->applyDamage(spell.getPower() * caster->m_currentAttributes->power / target->m_currentAttributes->resilience);
			}
		}
	}
}
