#include "BumpEffect.hpp"
#include <iostream>

namespace tacticode
{
	namespace spell
	{
		BumpEffect::BumpEffect(std::shared_ptr<IEffect> effects)
		{
			m_effects.push_back(effects);
		}
		void	BumpEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			// if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
				std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
				engine::Vector2i d;
				std::shared_ptr<engine::Map> map = engine.getMap();
				for (std::list<std::shared_ptr<IEffect>>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
				{
					(*it)->applyEffect(caster, cell, engine, spell);
				}

				d.x = 0;
				d.y = 0;
				if (caster->getPosition().y == cell->getY())
					d.x = caster->getPosition().x - cell->getX() > 0 ? -1 : 1;
				else if (caster->getPosition().x == cell->getX())
					d.y = caster->getPosition().y - cell->getY() > 0 ? -1 : 1;
				if (map->isCellOnMap(cell->getX() + d.x, cell->getY() + d.y))
				{
					d.x = cell->getX() + d.x;
					d.y = cell->getX() + d.y;
					target->moveToCell(d);
				}
		}
	}
}
