#pragma once

#include "ISpell.hpp"

namespace tacticode
{
	namespace spell
	{
		class Spell : public ISpell
		{
		public:
			Spell(std::shared_ptr<IEffect> effect, std::string name, float power, size_t range, size_t cooldown, size_t active, size_t aoe, size_t los);
			virtual ~Spell() = default;
			virtual void castSpell();
			virtual const std::string& getName() const;
			virtual const float getPower() const;
			virtual const size_t getRange() const;
			virtual const size_t getCooldown() const;
			virtual const size_t getIsActive() const;
			virtual const size_t getAoe() const;
			virtual const size_t getLos() const;
		};
	}
}
