#pragma once

#include <string>
#include <list>
#include <memory>
#include "IEffect.hpp"

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
			std::list<std::shared_ptr<IEffect>> m_effects;
		public:
			virtual ~ISpell() = default;
			virtual void castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine) = 0;
			virtual const std::string& getName() const = 0;
			virtual const float getPower() const = 0;
			virtual const size_t getRange() const = 0;
			virtual const size_t getCooldown() const = 0;
			virtual const size_t getIsActive() const = 0;
			virtual const size_t getAoe() const = 0;
			virtual const size_t getLos() const = 0;
			virtual const std::list<std::shared_ptr<IEffect>> getEffects() const = 0;
		};
	}
}
