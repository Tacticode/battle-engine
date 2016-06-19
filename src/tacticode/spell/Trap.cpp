#include "Trap.hpp"

namespace tacticode
{
	namespace spell
	{
		Trap::Trap(std::shared_ptr<engine::Cell> cell, std::list<std::shared_ptr<IEffect> > effect, std::shared_ptr<engine::Character> caster, Spell spell)
			: m_pos(cell), m_effects(effect), m_caster(caster), m_spell(spell)
		{

		}

		void	Trap::applyEffect()
		{
			for (std::list<std::shared_ptr<IEffect>>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			{
				//TODO: getEntity on map cell!
				//(*it)->applyEffect(context.caster, context.cell, this);
			}
		}
	}
}
