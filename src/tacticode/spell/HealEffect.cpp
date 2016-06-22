#include "HealEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		HealEffect::HealEffect()
		{

		}
//add context as parameter
		void	HealEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell)
		{
			if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()))
			{
				std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
				if (target)
					target->applyHeal(spell.getPower() * caster->m_currentAttributes->power);
			}
		}
	}
}
