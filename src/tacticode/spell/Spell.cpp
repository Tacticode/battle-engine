#include "Spell.hpp"
#include "tacticode/utils/utils.hpp"
#include "IEffect.hpp"
#include "tacticode/engine/BattleEngine.hpp"

using tacticode::utils::Singleton;

namespace tacticode
{
	namespace spell
	{
		Spell::Spell(std::shared_ptr<IEffect> effect, std::string const& name, float power, size_t range, size_t cooldown, size_t active, size_t aoe, size_t los)
			: ISpell(name), m_power(power), m_range(range), m_cooldown(cooldown), m_isActive(active), m_aoe(aoe), m_los(los)
		{
			m_effects.push_back(effect);
		}
		void Spell::castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine)
		{
			auto caster = engine.getCharacter(casterId);
			for (std::list<std::shared_ptr<IEffect> >::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
			{
				(*it)->applyEffect(caster, cell, engine, *this);
			}
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
