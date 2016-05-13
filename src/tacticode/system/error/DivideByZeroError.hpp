#pragma once

#include <stdexcept>
#include <string>

namespace tacticode
{
	namespace system
	{
		class DivideByZeroError : public std::logic_error
		{
		public:
			DivideByZeroError()
				: std::logic_error("Tried to divide by zero")
			{}
			DivideByZeroError(const std::string& message)
				: std::logic_error("Tried to divide by zero: " + message)
			{}
			virtual ~DivideByZeroError() throw()
			{}
		};
	} // namespace system
} // namespace tacticode
