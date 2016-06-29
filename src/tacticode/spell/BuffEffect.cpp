#include "BuffEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		BuffEffect::BuffEffect(std::shared_ptr<IBuff> buff)
		{
			m_effects.push_back(effects);
		}
		void	BuffEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{

			if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
			{

			}
		}
	}
}
