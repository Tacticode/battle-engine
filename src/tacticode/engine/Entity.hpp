#pragma once

#include <vector>
#include <memory>

namespace tacticode
{
	namespace engine
	{
		class Entity {
		public:
			virtual void moveOn() {};
			virtual ~Entity() {}
		}
	}
}
