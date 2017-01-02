#include "CrossAoeEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		CrossAoeEffect::CrossAoeEffect(size_t aoe, std::shared_ptr<IEffect> effects)
			: m_aoe(aoe)
		{
			m_effects.push_back(effects);
		}
		void	CrossAoeEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			// if ((engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY())) || isSecondary != -1)
			// {
				std::list<std::shared_ptr<engine::Cell> > targets;
				std::shared_ptr<engine::Map> map = engine.getMap();
				
				// only check the origin cell once -PM
				if (map->isCellOnMap(cell->getX(), cell->getY()) && map->getCell(cell->getX(), cell->getY()).getCharacterId() != -1) {
					targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX(), cell->getY())));
				}
				
				for (size_t i = 1; i < m_aoe; ++i)
				{
					if (map->isCellOnMap(cell->getX() + i, cell->getY()) && map->getCell(cell->getX() + i, cell->getY()).getCharacterId() != -1)
						targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() + i, cell->getY())));
					if (map->isCellOnMap(cell->getX() - i, cell->getY()) && map->getCell(cell->getX() - i, cell->getY()).getCharacterId() != -1)
						targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() - i, cell->getY())));
					if (map->isCellOnMap(cell->getX(), cell->getY() + i) && map->getCell(cell->getX(), cell->getY() + i).getCharacterId() != -1)
						targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX(), cell->getY() + i)));
					if (map->isCellOnMap(cell->getX(), cell->getY() - i) && map->getCell(cell->getX(), cell->getY() - i).getCharacterId() != -1)
						targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX(), cell->getY() - i)));
					if (i < m_aoe -1)
					{
						if (map->isCellOnMap(cell->getX() + i, cell->getY() + i) && map->getCell(cell->getX() + i , cell->getY() + i).getCharacterId() != -1)
							targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() + i, cell->getY() + i)));
						if (map->isCellOnMap(cell->getX() + i, cell->getY() - i) && map->getCell(cell->getX() + i , cell->getY() - i).getCharacterId() != -1)
							targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() + i, cell->getY() - i)));
						if (map->isCellOnMap(cell->getX() - i, cell->getY() - i) && map->getCell(cell->getX() - i , cell->getY() - i).getCharacterId() != -1)
							targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() - i, cell->getY() - i)));
						if (map->isCellOnMap(cell->getX() - i, cell->getY() + i) && map->getCell(cell->getX() - i , cell->getY() + i).getCharacterId() != -1)
							targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() - i, cell->getY() + i)));
					}
				}

				for (std::list<std::shared_ptr<IEffect>>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
				{
					for (std::list<std::shared_ptr<engine::Cell>>::iterator it2 = targets.begin(); it2 != targets.end(); ++it2)
					{
						(*it)->applyEffect(caster, *it2, engine, spell);
					}
				}
				//}
		}
	}
}
