#include "Trap.hpp"


Trap::Trap(std::list<std::shared_ptr<IEffect> > effect, engine::Cell cell, std::shared_ptr<engine::Character> caster, Spell spell):
	m_effects(effect), m_post(cell), m_caster(caster), m_spell(spell)
{

}

void	Trap::applyEffect()
{
	for (std::list<std::shared_ptr<IEffect> >::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
	{
		//TODO: getEntity on map cell!
		//(*it)->applyEffect(context.caster, context.cell, this);
	}
}
