#include "spell.hpp"
#include <iostream>

namespace tacticode {
  namespace spell{
    void SpellFactory::init() {
      registerSpell("Fireball", std::make_shared<FireBall>());
      std::cerr << "spell factory initialised" << std::endl;
    }

    void SpellFactory::registerSpell(
				     std::string const& n,
				     std::shared_ptr<ASpell> spell) {
      _dictionary[n] = spell;
    }

    std::shared_ptr<ASpell> SpellFactory::get(std::string const& n) {
      return Cast<ASpell>(_dictionary[n]->clone());
    }

    SpellFactory::~SpellFactory() {		
    }
  }
}
