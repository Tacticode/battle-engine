#pragma once

#include "tacticode/engine/ICharacterScript.hpp"
#include "v8/include/v8.h"

#include <memory>

namespace tacticode{
namespace script{
	class Context;
	class Script;
	class CharacterScript : public engine::ICharacterScript{
		std::shared_ptr<Context> _context;
		std::shared_ptr<Script> _script;
		engine::BattleEngineContext _engineContext;
	public:
		CharacterScript();
		virtual void setScript(std::string const& script);
		virtual void run();
		virtual engine::BattleEngineContext *getBattleEngineContext();
		virtual ~CharacterScript();
	};
}//script
}//tacticode