#include <iostream>
#include "SpellFactory.hpp"
#include "DamageEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		void SpellFactory::init() {
			//spell registration : name, power, range, cooldown, active, aoe, los
			registerSpell("Fireball", std::make_shared<Spell>(std::make_shared<DamageEffect>(),
					"Fireball",1,5,1,1,1,1));
			registerSpell("Holy Hand", std::make_shared<Spell>(std::make_shared<HealEffect>(),
					"Holy Hand",0.7,3,1,1,1,1));
			registerSpell("Snipe", std::make_shared<Spell>(std::make_shared<DamageEffect>(),
					"Snipe",1,7,1,1,1,1));
			registerSpell("Fire Trap", std::make_shared<Spell>(std::make_shared<TrapEffect>(std::make_shared<DamageEffect>()),
					"Fire Trap",0.8,5,3,1,1,1));
			std::cerr << "spell factory initialised" << std::endl;
		}

		void SpellFactory::registerSpell(
			std::string const& n,
			std::shared_ptr<Spell> spell) {
			_dictionary[n] = spell;
		}

		std::shared_ptr<Spell> SpellFactory::get(std::string const& n) {
			return (_dictionary[n]);
		}

		SpellFactory::~SpellFactory() {
		}
	}
}
