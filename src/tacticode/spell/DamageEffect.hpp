#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		class Spell{};
		class DamageEffect : public IEffect
		{
		public:
			virtual ~DamageEffect() = default;
			virtual void applyEffect();
		};
	}
}
