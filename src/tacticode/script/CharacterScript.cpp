#include "tacticode/utils/utils.hpp"
#include "script_intern.hpp"
#include <iostream>
namespace tacticode{
namespace script{
	CharacterScript::CharacterScript() {
		auto engine = utils::Singleton<ScriptFactory>::GetInstance();
		_context = engine->newContext();
		_context->embed(Context::BATTLE_ENGINE, getBattleEngineContext());
	}

	engine::BattleEngineContext *CharacterScript::getBattleEngineContext() {
		return &_engineContext;
	}

	void CharacterScript::setScript(std::string const& script){
		std::cerr << "set script" << std::endl;
		_context->get()->Enter();
		_script = std::make_shared<Script>(*_context, script);		
		_script->run(_context);
		_context->get()->Exit();
	}
	void CharacterScript::run(){
		_context->get()->Enter();
		v8::Handle<v8::Object> global = _context->get()->Global();
		v8::Handle<v8::Value> value = global->Get(v8String::fromString("onTurn")); 

		if (value->IsFunction()) {
		    v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
		    v8::Handle<v8::Value> args[2];

		    v8::Handle<v8::Value> js_result = func->Call(global, 0, args);
		} else {
			std::cerr << "onTurn undefined" << std::endl;
		}
		_context->get()->Exit();
	}

	CharacterScript::~CharacterScript(){

	}
}//script
}//tacticode