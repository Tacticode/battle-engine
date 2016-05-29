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
			DamageEffect();
			virtual ~DamageEffect() = default;
			virtual void applyEffect();
		};
	}
}
