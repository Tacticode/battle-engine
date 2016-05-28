#pragma once
// factory method to craft spells
#include <string>
#include <map>
#include <memory>

namespace tacticode{
  // i suggest migrate this later into engine
  using namespace spell
  {
    
    class SpellFactory {
      std::map<std::string, std::shared_ptr<ASpell> >
      _dictionary;
    public:
      // initialise spell lists
      // temporary for test
      // later may use json or other format instead of hard code in function
      void init(); 
      void registerSpell(std::string const &, std::shared_ptr<ASpell> );
      std::shared_ptr<ASpell> get(std::string const &);
      ~SpellFactory();
    };
  }
}
