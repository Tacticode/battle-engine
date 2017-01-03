#include "Spell.hpp"
#include "tacticode/utils/utils.hpp"
#include "IEffect.hpp"
#include "tacticode/engine/BattleEngine.hpp"
#include <cmath>

using tacticode::utils::Singleton;

namespace tacticode
{
	using engine::Vector2i;
	namespace spell
	{
		void ISpell::logCast(int id, int x, int y) {
			auto action = utils::Log::Action(id, x, y, "skill");
			action.add("skill", m_name);
			utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
		}

		Spell::Spell(std::shared_ptr<IEffect> effect, std::string const& name, float power, size_t minRange, size_t range, size_t cooldown, size_t active, size_t aoe, size_t los, size_t nbTurn)
			: ISpell(name)
		{
			m_effects.push_back(effect);
			m_power = power;
			m_minRange = minRange;
			m_range = range;
			m_cooldown = cooldown;
			m_isActive = active;
			m_aoe = aoe;
			m_los = los;
			m_nbTurn = nbTurn;
		}
		// Spell::Spell(const Spell &spell)
		// {
		//	m_name = spell.getName();
		//	m_power = spell.getPower();
		//	m_range = spell.getRange();
		//	m_cooldown = spell.getCooldown();
		//	m_isActive = spell.getIsActive();
		//	m_aoe = spell.getAoe();
		//	m_los = spell.getLos();
		//	m_effects = spell.getEffects();
		// }
		bool Spell::castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine)
		{
			auto caster = engine.getCharacter(casterId);
			Vector2i const& stpos = caster->getPosition();
			Vector2i edpos(cell->getX(), cell->getY());
			auto map = engine.getMap();

			int distance = std::abs(stpos.x - edpos.x) + std::abs(stpos.y - edpos.y);
			if (distance < m_minRange || distance > m_range) return false;
			
			if (map->reachLineOfSight(stpos, edpos)) {
				logCast(casterId, edpos.x, edpos.y);

				for (std::list<std::shared_ptr<IEffect> >::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
				{
					(*it)->applyEffect(caster, cell, engine, *this);
				}
				return true;
			} else {
				auto action = utils::Log::Action(casterId, edpos.x, edpos.y, "skill");
				action.add("skill", m_name);
				action.add("blocked", true);
				utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
				return false;
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
		const size_t Spell::getNbTurn() const
		{
			return m_nbTurn;
		}

		std::list<std::shared_ptr<IEffect> > Spell::getEffects() const
		{
			return m_effects;
		}
	}
}
