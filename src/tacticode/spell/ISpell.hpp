#pragma once

#include <string>
#include <list>
#include <memory>
#include <iostream>

namespace tacticode
{
	namespace engine
	{
		class Character;
		class Cell;
		class BattleEngine;
	}
	namespace spell
	{
		class IEffect;
		class ISpell
		{
		protected:
			std::string m_name;
			float m_power;
			size_t m_range;
			size_t m_aoe;
			size_t m_cooldown;
			size_t m_los;
			size_t m_isActive;
			size_t m_nbTurn;
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			ISpell(std::string const& name) : m_name(name) {};
			virtual ~ISpell() = default;
			void logCast(int caster, int x, int y); //a helper function to centralize log cast
			virtual void castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine) = 0;

			virtual const std::string& getName() const {return m_name;}
			virtual const float getPower() const {return m_power;}
			virtual const size_t getRange() const {return m_range;}
			virtual const size_t getCooldown() const {return m_aoe;}
			virtual const size_t getIsActive() const {return m_isActive;}
			virtual const size_t getAoe() const {return m_aoe;}
			virtual const size_t getLos() const {return m_los;}
			virtual const size_t getNbTurn() const {return m_nbTurn;}
			virtual std::list<std::shared_ptr<IEffect> > getEffects(){return m_effects;};
		};
	}
}
