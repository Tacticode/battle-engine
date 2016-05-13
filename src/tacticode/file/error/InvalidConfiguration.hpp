#pragma once

#include <stdexcept>

namespace tacticode
{
	namespace file
	{
		namespace error
		{
			class InvalidConfiguration : public std::runtime_error
			{
			public:
				InvalidConfiguration(const std::string& module, const std::string& message) :
					std::runtime_error("Failed to load " + module + " configuration: " + message)
				{}
			};
		} // namespace error
	} // namespace engine
} // namespace tacticode
