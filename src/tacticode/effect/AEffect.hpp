#pragma once

#include "IEffect.hpp"

namespace tacticode
{
	namespace engine
	{
		class Character;
	}

	namespace effect
	{
		class AEffect : public IEffect
		{
		public:
			virtual ~AEffect() = default;

			virtual void apply(engine::Character& character);
			virtual const std::string& getName() const;
		};
	}
}