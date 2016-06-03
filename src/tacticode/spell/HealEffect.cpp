#include "HealEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		HealEffect::HealEffect()
		{

		}
//add context as parameter
		void	HealEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, Spell spell)
		{
			int los = 1;
			if (los == true)
			{
				std::shared_ptr<engine::Character> target = nullptr; //==cell.getEntity()
				if (target)
					target->applyHeal(spell.getPower() * caster->m_currentAttributes->power);
			}
		}
	}
}
