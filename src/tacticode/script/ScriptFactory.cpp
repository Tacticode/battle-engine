#include "Context.hpp"
#include "tacticode/script/ScriptFactory.hpp"
#include "api/ApiCollection.hpp"
#include "script_intern.hpp"
#include "v8/include/v8.h"
#include "tacticode/utils/utils.hpp"

#include "tacticode/utils/Singleton.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <functional>
/* *******************************************************************
 * Script Factory
 * ******************************************************************/     

namespace {
	class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
	 public:
	  virtual void* Allocate(size_t length) {
	    void* data = AllocateUninitialized(length);
	    return data == NULL ? data : memset(data, 0, length);
	  }
	  virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
	  virtual void Free(void* data, size_t) { free(data); }
	  virtual ~ArrayBufferAllocator() {};
	};
}

using tacticode::utils::Singleton;
using tacticode::utils::Configuration;

namespace tacticode{
namespace script{
	/* *******************************************************************
	 * Initialize v8 engine instance
	 * ******************************************************************/
	ScriptFactory::ScriptFactory(){
		auto conf = Singleton<Configuration>::GetInstance()->value();	
		std::string argv0 = conf.getString("startup_path");

		//DEBUG_LOG() << argv0 << std::endl;

		v8::V8::InitializeICU();
		#if defined(WIN32)
		//v8::V8::InitializeExternalStartupData(argv0.c_str());
		#else
		v8::V8::InitializeExternalStartupData(argv0.c_str());
		#endif
		//Initialize platform
		_platform = v8::platform::CreateDefaultPlatform();
			v8::V8::InitializePlatform(_platform);
			v8::V8::Initialize();

		//Initialize Isolate
		v8::Isolate::CreateParams create_params;
			create_params.array_buffer_allocator = new ::ArrayBufferAllocator;
			_isolate = v8::Isolate::New(create_params);
			_isolate->Enter();
	}
	
	/* *******************************************************************
	 * Clean up
	 * ******************************************************************/
	ScriptFactory::~ScriptFactory(){
		_isolate->Exit();
		_isolate->Dispose();
	    v8::V8::Dispose();
		v8::V8::ShutdownPlatform();
		delete _platform;
	}

	/* *******************************************************************
	 * Return a new context
	 * ******************************************************************/
	std::shared_ptr<Context> ScriptFactory::newContext() {
		auto c = std::make_shared<Context>(_isolate);
		c->get()->Enter();
		utils::Singleton<api::ApiCollection>::GetInstance()->injectApi(c);
		c->get()->Exit();
		return c;
	}

	 std::shared_ptr<engine::ICharacterScript> ScriptFactory::newCharacterScript() {
		return std::make_shared<CharacterScript>();
	 }


	v8::Isolate *ScriptFactory::getEngine() {
		return _isolate;
	}

}//script
}//tacticode