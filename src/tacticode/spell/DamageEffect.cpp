#include "DamageEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		DamageEffect::DamageEffect()
		{
		}
//add context as parameter
		void	DamageEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell)
		{
			if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()))
			{
				std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
				if (target)
					target->applyDamage(spell.getPower() * caster->m_currentAttributes->power / target->m_currentAttributes->resilience);
			}
		}
	}
}
