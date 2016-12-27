#include "BuffEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		BuffEffect::BuffEffect(size_t nbTurn, std::shared_ptr<IEffect> effects)
			:m_nbTurn(nbTurn)
		{
			m_effects.push_back(effects);
		}
		void	BuffEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			m_caster = caster;
			// if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
			// {

			// }
			m_spell = std::make_shared<Spell>(spell);
			std::shared_ptr<engine::Map> map = engine.getMap();
			if (map->isCellOnMap(cell->getX(), cell->getY()))
			{
				std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
				if (target)
					target->addBuff(std::make_shared<Spell>(spell));
			}
		}
		void	BuffEffect::applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine)
		{
			std::shared_ptr<engine::Map> map = engine.getMap();

			for (std::list<std::shared_ptr<IEffect>>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			{
				(*it)->applyEffect(m_caster, std::make_shared<engine::Cell>(map->getCell(target->getPosition())), engine, *m_spell);
			}
			m_nbTurn--;
		}
	}
}
