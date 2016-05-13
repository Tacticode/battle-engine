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
			virtual ~IEffect() = default;

			virtual void apply(engine::Character& character) = 0;
			virtual const std::string& getName() const = 0;
		};
	}
}