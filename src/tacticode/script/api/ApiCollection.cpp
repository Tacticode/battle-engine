#include "api_intern.hpp"

#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/utils/Singleton.hpp"
#include "tacticode/script/script_intern.hpp"

#include <sstream>
#include <iostream>

using tacticode::utils::Singleton;
using tacticode::script::ScriptFactory;

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
}

ApiCollection::~ApiCollection() {
}


}//api
}//script
}//tacticode
