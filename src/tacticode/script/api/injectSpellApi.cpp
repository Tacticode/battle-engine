#include "api_intern.hpp"

#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/spell/SpellFactory.hpp"
#include "tacticode/utils/Singleton.hpp"
#include "tacticode/script/script_intern.hpp"
#include "tacticode/system/Vector2.hpp"

#include <sstream>
#include <iostream>
#include <cassert>

#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/engine/Character.hpp"
#include "tacticode/utils/FightLogger.hpp"

#include "injectSpellApi.hpp"

using tacticode::utils::Singleton;
using tacticode::script::ScriptFactory;
using tacticode::script::v8String;
using tacticode::script::Context;

namespace {
	using namespace tacticode;

  void functionMoveToCell(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::EscapableHandleScope scope(args.GetIsolate());
	v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
	bool rt = false;
	//BattleEngineContext stored in global of the context
	tacticode::engine::BattleEngineContext *battle_context = reinterpret_cast<tacticode::engine::BattleEngineContext*>(
		context->GetAlignedPointerFromEmbedderData(Context::BATTLE_ENGINE));

	assert(battle_context);

	auto character = battle_context->character;

	assert(character);
	if (args.Length() >= 2) {
		v8::Local<v8::Value> argX = args[0];
		v8::Local<v8::Value> argY = args[1];
		if (argX->IsNumber() && argY->IsNumber()) {
			int x = argX->ToNumber()->Value();
			int y = argY->ToNumber()->Value();
			rt = character->moveToCell(engine::Vector2i(x, y));

			auto action = utils::Log::Action(character->getId(), x, y, "move");
			action.add("success", rt);
			utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
		}
	}
	v8::Local<v8::Value> result = v8::Boolean::New(args.GetIsolate(), rt);
	args.GetReturnValue().Set(scope.Escape(result));
  }

  void functionSpell(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::EscapableHandleScope scope(args.GetIsolate());
	v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
	bool rt = false;
	//BattleEngineContext stored in global of the context
	tacticode::engine::BattleEngineContext *battle_context = reinterpret_cast<tacticode::engine::BattleEngineContext*>(
	  context->GetAlignedPointerFromEmbedderData(Context::BATTLE_ENGINE));

	assert(battle_context);

	auto character = battle_context->character;

	assert(character);
	if (args.Length() >= 2) {
	  v8::Local<v8::Value> spell = args[0];
	  v8::Local<v8::Value> argX = args[1];
	  v8::Local<v8::Value> argY = args[2];
	  if (spell->IsString() && argX->IsNumber() && argY->IsNumber()) {
		v8::String::Utf8Value utf8value(spell);
		std::string spell_str(*utf8value);
		int x = argX->ToNumber()->Value();
		int y = argY->ToNumber()->Value();

		auto map = battle_context->engine->getMap();
		auto facto = Singleton<spell::SpellFactory>::GetInstance();
		auto spell = facto->get(spell_str);
		if (spell) {
		  spell->castSpell(character, map->getManagedCell(x, y), *(battle_context->engine));
		  rt = true;
		}

		auto action = utils::Log::Action(character->getId(), x, y, spell_str);
		action.add("success", rt);
		utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
	  }
	}
	v8::Local<v8::Value> result = v8::Boolean::New(args.GetIsolate(), rt);
	args.GetReturnValue().Set(scope.Escape(result));
  }

}

namespace tacticode{
namespace script{
namespace api{

void injectSpellApi(std::shared_ptr<Context> context) {
  v8::Isolate *isolate = Singleton<ScriptFactory>::GetInstance()->getEngine();

  auto global = context->get()->Global();
  global->Set(v8String::fromString("spell"), v8::Function::New(isolate, functionSpell));
}

}//api
}//script
}//tacticode
