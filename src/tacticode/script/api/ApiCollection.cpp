#include "api_intern.hpp"

#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/utils/Singleton.hpp"
#include "tacticode/script/script_intern.hpp"

#include <sstream>
#include <iostream>
#include <cassert>

#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/engine/Character.hpp"

using tacticode::utils::Singleton;
using tacticode::script::ScriptFactory;
using tacticode::script::v8String;
using tacticode::script::Context;

namespace {
  void functionLog(const v8::FunctionCallbackInfo<v8::Value>& args) {
  	std::ostringstream stringStream;
			    stringStream << "{\"type\":\"console\", \"data\":\"";
			    if (args.Length() >= 1) {
			    v8::HandleScope scope(args.GetIsolate());
			    v8::Local<v8::Value> arg = args[0];
			    v8::String::Utf8Value value(arg);

			    stringStream << *value;
			    }
			    stringStream << "\"}";
			    std::cerr << stringStream.str();
  }

  void functionFireBall(const v8::FunctionCallbackInfo<v8::Value>& args) {
    if (args.Length() >= 2) {
    v8::HandleScope scope(args.GetIsolate());
    v8::Local<v8::Value> argX = args[0];
    v8::Local<v8::Value> argY = args[0];

    (void)argX;
    (void)argY;
    //Todo, fireball somehow
    }
  }

  void functionGetCurrentEntity(const v8::FunctionCallbackInfo<v8::Value>& args) {
  	v8::EscapableHandleScope scope(args.GetIsolate());
  	v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

  	//BattleEngineContext stored in global of the context
  	tacticode::engine::BattleEngineContext *battle_context = reinterpret_cast<tacticode::engine::BattleEngineContext*>(
  		context->GetAlignedPointerFromEmbedderData(Context::BATTLE_ENGINE));

  	assert(battle_context);

  	tacticode::engine::Character *character = battle_context->character;

  	assert(character);

  	v8::Local<v8::Object> result = v8::Object::New(args.GetIsolate());

  	//no coordinate in character?!!
		//result->Set(context, v8String::fromString("x"), v8::Number::New(args.GetIsolate(), character->x));

		result->Set(context, v8String::fromString("name"), v8String::fromString(character->m_name));
		//breed is an integer? wut
		//result->Set(context, v8String::fromString("breed"), v8String::fromString(character->m_breed));

		result->Set(context, v8String::fromString("team"), v8::Number::New(args.GetIsolate(), character->m_teamId));

  	args.GetReturnValue().Set(scope.Escape(result));
  }

}

namespace tacticode{
namespace script{
namespace api{

ApiCollection::ApiCollection() {
}

void ApiCollection::injectApi(std::shared_ptr<tacticode::script::Context> context) {
	v8::Isolate *isolate = Singleton<ScriptFactory>::GetInstance()->getEngine();

	auto global = context->get()->Global();
	{
		//Inject a function like this
		tacticode::script::v8String funcName("$log");
		global->Set(funcName.get(), v8::Function::New(isolate, functionLog));		
	}

	{
		tacticode::script::v8String funcName("$fireball");
		global->Set(funcName.get(), v8::Function::New(isolate, functionFireBall));
	}	
	global->Set(v8String::fromString("getCurrentEntity"), v8::Function::New(isolate, functionGetCurrentEntity));
}

ApiCollection::~ApiCollection() {
}


}//api
}//script
}//tacticode
