#include "LineAoeEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		LineAoeEffect::LineAoeEffect(size_t aoe, std::shared_ptr<IEffect> effects)
			: m_aoe(aoe)
		{
			m_effects.push_back(effects);
		}
		void	LineAoeEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			utils::Log log;
			auto fightLog = utils::Singleton<utils::FightLogger>::GetInstance();
			if ((engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) &&
				(caster->getPosition().x == cell->getX() ||
					caster->getPosition().y == cell->getY())) || isSecondary != -1)
			{
				std::list<std::shared_ptr<engine::Cell> > targets;
				engine::Vector2i d;
				std::shared_ptr<engine::Map> map = engine.getMap();
				log.add("SPELLTYPE", "aoe in line");
				fightLog->addAction(log);
				d.x = 0;
				d.y = 0;
				if (caster->getPosition().y == cell->getY())
					d.x = caster->getPosition().x - cell->getX() > 0 ? -1 : 1;
				else if (caster->getPosition().x == cell->getX())
					d.y = caster->getPosition().y - cell->getY() > 0 ? -1 : 1;
				for (size_t i = 0; i < m_aoe; ++i)
				{
					if (engine.getCharacter(map->getCell(cell->getX() + (i * d.x), cell->getY() + (i * d.y)).getCharacterId()))
						targets.push_back(std::make_shared<engine::Cell>(map->getCell(cell->getX() + (i * d.x), cell->getY() + (i * d.y))));
				}

				for (std::list<std::shared_ptr<IEffect>>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
				{
					for (std::list<std::shared_ptr<engine::Cell>>::iterator it2 = targets.begin(); it2 != targets.end(); ++it2)
						(*it)->applyEffect(caster, *it2, engine, spell);
				}
			}
		}
	}
}
