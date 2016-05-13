#pragma once

#include <stdexcept>

namespace melon
{
	namespace engine
	{
		namespace error
		{
			class InvalidSubscribeLocation : public std::runtime_error
			{
			public:
				InvalidSubscribeLocation() :
					std::runtime_error(
						"Tried to subscribe or unsubscribe from a system during the iteration")
				{}
			};
		} // namespace error
	} // namespace engine
} // namespace melon
