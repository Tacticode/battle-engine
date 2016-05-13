#include "Character.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "tacticode/spell/ISpell.hpp"

namespace tacticode
{
	namespace engine
	{
		Character::Character(Attributes & baseAttributes)
			: m_baseAttributes(baseAttributes)
		{
		}

		void Character::applyEffects()
		{
			for (auto effect : m_effects)
			{
				effect->apply(*this);
			}
		}

		void Character::play()
		{
			applyEffects();
			executeScript();
		}

		void Character::executeScript()
		{
		}

		void Character::setScript(const std::string & script)
		{
		}

		void Character::addEffect(std::shared_ptr<effect::IEffect> effect)
		{
			m_effects.push_back(effect);
		}
	}
}