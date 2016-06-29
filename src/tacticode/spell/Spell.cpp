#include "Spell.hpp"

namespace tacticode
{
	namespace spell
	{
		Spell::Spell(std::shared_ptr<IEffect> effect, std::string name, float power, size_t range, size_t cooldown, size_t active, size_t aoe, size_t los)
			: m_name(name), m_power(power), m_range(range), m_cooldown(cooldown), m_isActive(active), m_aoe(aoe), m_los(los)
		{
			m_effects.push_back(effect);
		}
		void Spell::castSpell(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine)
		{
			utils::Log log;
			auto fightLog = utils::Singleton<utils::FightLogger>::GetInstance();
			log.add("LAUNCHSPELL", m_name);
			fightLog->addAction(log);
			for (std::list<std::shared_ptr<IEffect> >::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			{
				(*it)->applyEffect(caster, cell, engine, *this);
			}
		}

		const std::string& Spell::getName() const
		{
			return m_name;
		}
		const float Spell::getPower() const
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
