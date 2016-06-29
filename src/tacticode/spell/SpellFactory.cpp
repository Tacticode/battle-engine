#include <iostream>
#include "SpellFactory.hpp"
#include "DamageEffect.hpp"
#include "HealEffect.hpp"
#include "TrapEffect.hpp"
#include "LineAoeEffect.hpp"
#include "CrossAoeEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		void SpellFactory::init() {
			//spell registration : name, power, range, cooldown, active, aoe, los
			registerSpell("FIREBALL", std::make_shared<Spell>(std::make_shared<DamageEffect>(),
					"FIREBALL",1,5,1,1,1,1));
			registerSpell("HOLY_HAND", std::make_shared<Spell>(std::make_shared<HealEffect>(),
					"HOLY_HAND",0.7,3,1,1,1,1));
			registerSpell("SNIPE", std::make_shared<Spell>(std::make_shared<DamageEffect>(),
					"SNIPE",1,7,1,1,1,1));
			registerSpell("FIRE_TRAP", std::make_shared<Spell>(std::make_shared<TrapEffect>(std::make_shared<DamageEffect>()),
					"FIRE_TRAP",0.8,5,3,1,1,1));
			registerSpell("PASS_THROUGH_ARROW", std::make_shared<Spell>(std::make_shared<LineAoeEffect>(5, std::make_shared<DamageEffect>()),
					"PASS_THROUGH_ARROW",0.8,3,5,1,1,1));
			registerSpell("SMASH", std::make_shared<Spell>(std::make_shared<LineAoeEffect>(2, std::make_shared<DamageEffect>()),
					"SMASH",2,1,2,1,2,1));
			registerSpell("BLADESTORM", std::make_shared<Spell>(std::make_shared<CrossAoeEffect>(2, std::make_shared<DamageEffect>()),
					"BLADESTORM",1,1,1,1,2,1));
			registerSpell("METEORE", std::make_shared<Spell>(std::make_shared<CrossAoeEffect>(3, std::make_shared<DamageEffect>()),
					"METEORE",1.5,5,3,1,3,1));
			std::cerr << "spell factory initialised" << std::endl;
		}

		void SpellFactory::registerSpell(
			std::string const& n,
			std::shared_ptr<Spell> spell) {
			m_dictionary[n] = spell;
		}

		std::shared_ptr<Spell> SpellFactory::get(std::string const& n) {
			return (m_dictionary[n]);
		}

		SpellFactory::~SpellFactory() {
		}
	}
}
