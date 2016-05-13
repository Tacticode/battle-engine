#include "AEffect.hpp"

namespace tacticode
{
	namespace effect
	{
		void AEffect::apply(engine::Character & character)
		{
		}

		const std::string& AEffect::getName() const
		{
			return m_name;
		}
	}
}