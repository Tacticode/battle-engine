#include "DamageEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		DamageEffect::DamageEffect()
		{

		}
//add context as parameter
		void	DamageEffect::ApplyEffect(Spell spell, Engine::Character caster, Engine::Cell cell)
		{
			//if (los == true)
			Engine::Character target = NULL; //==cell.getEntity()
			if (target)
			{
				target.applyDamages(spell.getPower() * caster.m_currentAttributes.power / target.m_currentAttributes.resilience);
			}
		}
	}
}
