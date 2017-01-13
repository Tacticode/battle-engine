#include "RemoveSpeedEffect.hpp"
#include <iostream>

namespace tacticode
{
	namespace spell
	{
		RemoveSpeedEffect::RemoveSpeedEffect(int speedChange)
			:m_speedChange(speedChange)
		{
		}
		void	RemoveSpeedEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			// if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
			std::shared_ptr<engine::Character> target = engine.getCharacter(cell->getCharacterId());
			target->changeMoveSpeed(m_speedChange);
		}
	}
}
