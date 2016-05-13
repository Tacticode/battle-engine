#pragma once

#include <string>

namespace tacticode
{
	namespace spell
	{
		class ISpell
		{
		protected:
			std::string m_name;

		public:
			virtual ~ISpell() = default;

			virtual const std::string& getName() const = 0;
		};
	}
}