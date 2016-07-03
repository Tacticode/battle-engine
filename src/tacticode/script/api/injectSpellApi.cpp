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
			int32_t x = static_cast<int32_t>(argX->ToNumber()->Value());
			int32_t y = static_cast<int32_t>(argY->ToNumber()->Value());
		    rt = character->moveToCell(engine::Vector2i(x, y));
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
}

}//api
}//script
}//tacticode
