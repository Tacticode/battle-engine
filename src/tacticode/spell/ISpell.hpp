#pragma once

#include <string>
#include <list>
#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class ISpell
		{
		protected:
			std::string m_name;
			size_t m_power;
			size_t m_range;
			size_t m_aoe;
			size_t m_cooldown;
			size_t m_los;
			size_t m_isACtif;
			std::list<IEffect> m_effects;
		public:
			virtual ~ISpell() = default;
			virtual const std::string& getName() const = 0;
			virtual const size_t getPower() const = 0;
			virtual const size_t getRange() const = 0;
			virtual const size_t getCooldown() const = 0;
			virtual const size_t getIsActif() const = 0;
			virtual const size_t getAoe() const = 0;
			virtual const size_t getLos() const = 0;
		};
	}
}
