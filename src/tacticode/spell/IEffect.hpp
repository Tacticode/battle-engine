#pragma once

#include <string>
#include <list>
#include <memory>
#include "tacticode/engine/Character.hpp"

namespace tacticode
{
	namespace engine
	{
		class Character;
		class Cell;
	}
	namespace spell
	{
		class Spell;
		class IEffect{
		public:
			virtual ~IEffect() = default;
			virtual void applyEffect(std::shared_ptr<engine::Character> caster, std::shared_ptr<engine::Cell> cell, Spell spell) = 0;
		};
	}
}
