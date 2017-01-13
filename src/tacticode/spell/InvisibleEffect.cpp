#include "InvisibleEffect.hpp"
#include <iostream>

namespace tacticode
{
	namespace spell
	{
		InvisibleEffect::InvisibleEffect()
		{
		}
		void	InvisibleEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			// if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
			{
				std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
				if (target)
				{
					target->becomeInvisible();
				}
			}
		}
	}
}
