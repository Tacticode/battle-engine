#pragma once

#include "ISpell.hpp"

namespace tacticode
{
	namespace spell
	{
		class IEffect;
		class Spell : public ISpell
		{
		public:
			Spell(std::shared_ptr<IEffect> effect, std::string const& name, float power, size_t range, size_t cooldown, size_t active, size_t aoe, size_t los, size_t nbTurn = 1);
			//Spell(const Spell &spell);
			virtual ~Spell() = default;
			void castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine);
			virtual const float getPower() const;
			virtual const size_t getRange() const;
			virtual const size_t getCooldown() const;
			virtual const size_t getIsActive() const;
			virtual const size_t getAoe() const;
			virtual const size_t getLos() const;
			virtual const size_t getNbTurn() const;
			virtual std::list<std::shared_ptr<IEffect> > getEffects() const;
		};
	}
}
