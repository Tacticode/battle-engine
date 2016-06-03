#pragma once

/* *******************************************************************
 * Use this in a singleton
 * As a global handler a v8 instance
 *
 * @example
 * using ScriptFactory = utils::Singleton<script::ScriptFactory>
 * ******************************************************************/
#include "v8/include/v8.h"
#include "libplatform/libplatform.h"

#include "tacticode/engine/ICharacterScript.hpp"
#include <memory>
namespace tacticode{
namespace script{

class Context;
class ScriptFactory {
	v8::Platform* 				_platform;
	v8::Isolate 					*_isolate;
public:
	 ScriptFactory();
	 std::shared_ptr<Context> newContext();
	 std::shared_ptr<engine::ICharacterScript> newCharacterScript();
	 v8::Isolate *getEngine();
	 ~ScriptFactory();
};

}//script
}//tacticode

