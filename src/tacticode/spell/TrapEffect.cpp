#include "TrapEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		TrapEffect::TrapEffect(std::list<std::shared_ptr<IEffect> > effects)
			: m_effects(effects)
		{
		}
		void	TrapEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell)
		{
			int los = 1;// TODO replace by map méthod making the calcul between 2cells.
			if (los == true)
			{
				Trap(cell, m_effects, caster, spell);//Create a method to instantiate entity on a cel
			}
		}
	}
}
