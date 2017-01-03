#include <iostream>
#include "SpellFactory.hpp"
#include "DamageEffect.hpp"
#include "HealEffect.hpp"
#include "TrapEffect.hpp"
#include "LineAoeEffect.hpp"
#include "CrossAoeEffect.hpp"
#include "TrapSpell.hpp"
#include "BumpEffect.hpp"
#include "BuffEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		void SpellFactory::init() {
			//spell registration : name, power, range, cooldown, active, aoe, los
			registerSpell("FIREBALL", std::make_shared<Spell>(std::make_shared<DamageEffect>(),
					"FIREBALL",1,3,5,1,1,1,1));
			registerSpell("HOLY_HAND", std::make_shared<Spell>(std::make_shared<HealEffect>(),
					"HOLY_HAND",0.7,0,3,1,1,1,1));
			registerSpell("SNIPE", std::make_shared<Spell>(std::make_shared<DamageEffect>(),
					"SNIPE",1,0,7,1,1,1,1));
			registerSpell("FIRE_TRAP", std::make_shared<Spell>(std::make_shared<TrapEffect>(std::make_shared<DamageEffect>()),
					"FIRE_TRAP",0.8,0,5,3,1,1,1));
			registerSpell("GHOST_ARROW", std::make_shared<Spell>(std::make_shared<LineAoeEffect>(5, std::make_shared<DamageEffect>()),
					"GHOST_ARROW",0.8,0,3,5,1,1,1));
			registerSpell("SMASH", std::make_shared<Spell>(std::make_shared<LineAoeEffect>(2, std::make_shared<DamageEffect>()),
					"SMASH",2,0,1,2,1,2,1));
			registerSpell("BLADESTORM", std::make_shared<Spell>(std::make_shared<CrossAoeEffect>(2, std::make_shared<DamageEffect>()),
					"BLADESTORM",1,0,1,1,1,2,1));
			registerSpell("METEOR", std::make_shared<Spell>(std::make_shared<CrossAoeEffect>(3, std::make_shared<DamageEffect>()),
					"METEOR",1.5,3,5,3,1,3,1));
			registerSpell("TRAP", std::make_shared<TrapSpell>());
			registerSpell("SHIELD_BUMP", std::make_shared<Spell>(std::make_shared<BumpEffect>(std::make_shared<DamageEffect>()),
					"SHIELD_BUMP",1,0,1,3,1,1,1));
			registerSpell("SHIELD_BREAK", std::make_shared<Spell>(std::make_shared<CrossAoeEffect>(1, std::make_shared<BumpEffect>(nullptr)),
					"SHIELD_BREAK",1.5,0,5,3,1,3,1));
			registerSpell("CURSE", std::make_shared<Spell>(std::make_shared<BuffEffect>(3, std::make_shared<DamageEffect>()),
					"CURSE",1.5,0,5,3,1,3,1));
			std::cerr << "spell factory initialised" << std::endl;
		}

		void SpellFactory::registerSpell(
			std::string const& n,
			std::shared_ptr<ISpell> spell) {
			m_dictionary[n] = spell;
		}

		std::shared_ptr<ISpell> SpellFactory::get(std::string const& n) {
			if (m_dictionary.find(n) != m_dictionary.end())
				return (m_dictionary[n]);
			return nullptr;
		}

		SpellFactory::~SpellFactory() {
		}
	}
}
