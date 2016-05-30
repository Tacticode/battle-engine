#include "tacticode/script/ScriptFactory.hpp"

#include "v8/include/v8.h"
#include "v8/include/libplatform/libplatform.h"

#include "tacticode/utils/utils.hpp"

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
	  virtual ~ArrayBufferAllocator();
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

		DEBUG_LOG() << argv0 << std::endl;

		v8::V8::InitializeICU();
		v8::V8::InitializeExternalStartupData(argv0);
		//Initialize platform
		platform = v8::platform::CreateDefaultPlatform();
			v8::V8::InitializePlatform(platform);
			v8::V8::Initialize();

		//Initialize Isolate
		v8::Isolate::CreateParams create_params;
			create_params.array_buffer_allocator = new ::ArrayBufferAllocator;
			isolate = v8::Isolate::New(create_params);
			isolate->Enter();
	}
	
	/* *******************************************************************
	 * Clean up
	 * ******************************************************************/
	ScriptFactory::~ScriptFactory(){
		isolate->Exit();
		isolate->Dispose();
	    v8::V8::Dispose();
		v8::V8::ShutdownPlatform();
		delete platform;
	}
}//script
}//tacticode