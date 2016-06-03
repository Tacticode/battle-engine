#include <iostream>
#include "SpellFactory.hpp"
#include "DamageEffect.hpp"

namespace tacticode
{
	namespace spell
	{
		void SpellFactory::init() {
			registerSpell("Fireball", std::make_shared<Spell>(std::make_shared<DamageEffect>()));
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
