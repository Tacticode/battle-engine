#include "TrapEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		TrapEffect::TrapEffect(std::shared_ptr<IEffect>	 effects)
		{
			m_effects.push_back(effects);
		}
		void	TrapEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary)
		{
			std::shared_ptr<engine::Map> map = engine.getMap();
			if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()) || isSecondary != -1)
			{
				if (map->isCellFree(cell->getX(), cell->getY()))
					Trap(cell, m_effects, caster, spell);
			}
		}
	}
}
