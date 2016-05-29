#pragma once

#include "ISpell.hpp"

namespace tacticode
{
	namespace spell
	{
		class Spell : public ISpell
		{
		public:
			Spell();
			virtual ~Spell() = default;
			virtual const std::string& getName() const;
			virtual const size_t getPower() const;
			virtual const size_t getRange() const;
			virtual const size_t getCooldown() const;
			virtual const size_t getIsActive() const;
			virtual const size_t getAoe() const;
			virtual const size_t getLos() const;
		};
	}
}
