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
			utils::Log log;
			auto fightLog = utils::Singleton<utils::FightLogger>::GetInstance();
			for (std::list<std::shared_ptr<IEffect>>::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			{
				log.add("TRAPTRIGGER", m_spell.getName());
				fightLog->addAction(log);
				// (*it)->applyEffect(m_caster, m_pos, m_spell);
			}
		}
	}
}
