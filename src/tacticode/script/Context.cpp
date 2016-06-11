#include "Context.hpp"

namespace tacticode{
namespace script{
	Context::Context(v8::Isolate *isolate) {
		_resource = v8::Context::New(isolate);
//		_resource->Global()->SetInternalFieldCount(100);
	}

	Context::~Context() {
		
	}
}//script
}//tacticode