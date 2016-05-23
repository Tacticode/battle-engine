#include "Character.hpp"
#include "tacticode/effect/IEffect.hpp"
#include "tacticode/spell/ISpell.hpp"

namespace tacticode
{
	namespace engine
	{
		Character::Character(const file::IValue& json)
		{
			deserialize(json);
		}

		void Character::deserialize(const file::IValue& json)
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
			// TODO
		}

		void Character::setScript(const std::string & script)
		{
			m_script = script;
		}

		const std::string& Character::getScript() const
		{
			return m_script;
		}

		size_t Character::getTeamId() const
		{
			return m_teamId;
		}

		void Character::addEffect(std::shared_ptr<effect::IEffect> effect)
		{
			m_effects.push_back(effect);
		}
	}
}