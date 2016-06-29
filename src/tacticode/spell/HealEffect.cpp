#include "HealEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		HealEffect::HealEffect()
		{

		}
//add context as parameter
		void	HealEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			utils::Log log;
			auto fightLog = utils::Singleton<utils::FightLogger>::GetInstance();
			if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
			{
				std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
				log.add("HEAL", spell.getPower() * caster->m_currentAttributes->power);
				fightLog->addAction(log);
				if (target)
					target->applyHeal(spell.getPower() * caster->m_currentAttributes->power);
			}
		}
	}
}
