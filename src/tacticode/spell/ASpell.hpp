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
			ASpell(const ASpell&) = default;
			ASpell(ASpell&&) = default;
			ASpell& operator=(const ASpell&) = default;
			ASpell& operator=(ASpell&&) = default;

			virtual const std::string& getName() const;
		};
	}
}