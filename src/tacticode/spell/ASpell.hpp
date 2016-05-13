#pragma once

#include "ISpell.hpp"

namespace tacticode
{
	namespace engine
	{
		class Character;
	}

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

			virtual void apply(engine::Character& character);
			virtual const std::string& getName() const;
		};
	}
}