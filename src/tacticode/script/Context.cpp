#include "Context.hpp"

namespace tacticode{
namespace script{
	Context::Context(v8::Isolate *isolate) {
		_resource = v8::Context::New(isolate);
	}

	Context::Context(Context const& c) {
		_resource = c._resource;
	}
	Context& Context::operator=(Context const& c) {
		_resource = c._resource;
		return *this;
	}


	Context::~Context() {
		
	}
}//script
}//tacticode