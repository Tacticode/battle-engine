#pragma once

#include <string>
#include <list>
namespace tacticode
{
	namespace spell
	{
		class IEffect{
		public:
			virtual ~IEffect() = default;
			virtual void applyEffect() = 0;
		};
	}
}
