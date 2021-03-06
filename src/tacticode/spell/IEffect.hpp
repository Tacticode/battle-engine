#pragma once

#include <string>
#include <list>
#include <memory>
#include "tacticode/engine/Character.hpp"
#include "tacticode/engine/Cell.hpp"
#include "tacticode/engine/Map.hpp"
#include "tacticode/utils/utils.hpp"
#include "tacticode/engine/BattleEngine.hpp"

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
		class Spell;
		class IEffect{
		protected:
			std::shared_ptr<engine::Character> m_caster;
		public:
			virtual ~IEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, engine::BattleEngine &engine, Spell spell, int isSecondary = -1) = 0;
			virtual void applyBuff(std::shared_ptr<engine::Character> target, engine::BattleEngine &engine) = 0;
		};
	}
}
