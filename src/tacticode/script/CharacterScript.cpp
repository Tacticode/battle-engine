#include "tacticode/utils/utils.hpp"
#include "script.hpp"
#include "Script.hpp"
#include <iostream>
namespace tacticode{
namespace script{
	CharacterScript::CharacterScript() {
		auto engine = utils::Singleton<ScriptFactory>::GetInstance();
		_context = engine->newContext();
	}

	void CharacterScript::setScript(std::string const& script){
		std::cerr << "set script" << std::endl;
		_context->get()->Enter();
		_script = std::make_shared<Script>(*_context, script);		
		_context->get()->Exit();
	}
	void CharacterScript::run(){
		_context->get()->Enter();
		_script->run(_context);
		_context->get()->Exit();
	}

	CharacterScript::~CharacterScript(){

	}
}//script
}//tacticode