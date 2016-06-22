#include "TrapEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		TrapEffect::TrapEffect(std::shared_ptr<IEffect>	 effects)
		{
			m_effects.push_back(effects);
		}
		void	TrapEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell)
		{
			if (engine.getMap()->hasCellLineOfSightOnCell(caster->getPosition().x, caster->getPosition().y, cell->getX(), cell->getY()))
			{
				Trap(cell, m_effects, caster, spell);//Create a method to instantiate entity on a cel
			}
		}
	}
}
