#pragma once
// factory method to craft spells
#include <string>
#include <map>
#include <memory>
#include "Spell.hpp"

namespace tacticode{
  // i suggest migrate this later into engine
  namespace spell
  {

	class SpellFactory {
	  std::map<std::string, std::shared_ptr<ISpell>> m_dictionary;
	public:
	  // initialise spell lists
	  // temporary for test
	  // later may use json or other format instead of hard code in function
	  void init();
	  void registerSpell(std::string const &, std::shared_ptr<ISpell> );
	  std::shared_ptr<ISpell> get(std::string const &);
	  ~SpellFactory();
	};
  }
}
