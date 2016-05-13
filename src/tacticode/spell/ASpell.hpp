#pragma once

#include "ISpell.hpp"

namespace tacticode
{
	namespace spell
	{
		class ASpell : public ISpell
		{
		public:
			virtual ~ASpell() = default;

			virtual const std::string& getName() const;
		};
	}
}