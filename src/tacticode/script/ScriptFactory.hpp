#pragma once

/* *******************************************************************
 * Use this in a singleton
 * As a global handler a v8 instance
 *
 * @example
 * using ScriptFactory = utils::Singleton<script::ScriptFactory>
 * ******************************************************************/

namespace tacticode{
namespace script{

class ScriptFactory {
	v8::Platform* 				_platform;
	v8::Isolate 					*_isolate;

public:
	 ScriptFactory();
	 ~ScriptFactory();
};

}//script
}//tacticode

