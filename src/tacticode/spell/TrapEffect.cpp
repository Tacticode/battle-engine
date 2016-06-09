#include "TrapEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		TrapEffect::TrapEffect(std::list<std::shared_ptr<IEffect> > effects)
			: m_effects(effects)
		{
		}
//add context as parameter
		void	TrapEffect::applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, Spell spell)
		{
			int los = 1;// TODO replace by map méthod making the calcul between 2cells.
			if (los == true)
			{
				Trap(m_effects, cell, caster, spell);//Crete a method to instantiate entity on a cell.
			}
		}
	}
}
