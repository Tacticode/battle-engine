#include "Spell.hpp"

namespace tacticode
{
	namespace spell
	{
		Spell::Spell(){

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
