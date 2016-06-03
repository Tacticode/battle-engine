#include "Spell.hpp"

namespace tacticode
{
	namespace spell
	{
		Spell::Spell(std::shared_ptr<IEffect> effect){
			m_effects.push_back(effect);
		}

		void Spell::castSpell()
		{
			for (std::list<std::shared_ptr<IEffect> >::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			{
				//(*it)->applyEffect(context.caster, context.cell, this);
			}
		}

		const std::string& Spell::getName() const
		{
			return m_name;
		}
		const size_t Spell::getPower() const
		{
			return m_power;
		}
		const size_t Spell::getRange() const
		{
			return m_range;
		}
		const size_t Spell::getAoe() const
		{
			return m_aoe;
		}
		const size_t Spell::getCooldown() const
		{
			return m_cooldown;
		}
		const size_t Spell::getIsActive() const
		{
			return m_isActive;
		}
		const size_t Spell::getLos() const
		{
			return m_los;
		}
	}
}
