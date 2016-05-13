#pragma once

#include <string>

namespace tacticode
{
	namespace engine
	{
		class Character;
	}

	namespace effect
	{
		class IEffect
		{
		protected:
			std::string m_name;

		public:
			virtual ~IEffect()                 = default;
			IEffect(const IEffect&)            = default;
			IEffect(IEffect&&)                 = default;
			IEffect& operator=(const IEffect&) = default;
			IEffect& operator=(IEffect&&)      = default;

			virtual void apply(engine::Character& character) = 0;
			virtual const std::string& getName() const = 0;
		};
	}
}