#include "Context.hpp"
#include "Script.hpp"

#include "tacticode/utils/utils.hpp"
#include "script.hpp"

namespace tacticode{
namespace script{
	/* *******************************************************************
	 * compile the script
	 * ******************************************************************/	        
	Script::Script(Context &context, std::string const& rawscript) {
		v8String script_str(rawscript);

		_resource = v8::Script::Compile(context.get(), script_str.get()).ToLocalChecked();
	}

	void Script::run(std::shared_ptr<Context> context) {
		_resource->Run(context->get());
	}

	Script::~Script() {
		
	}

}//script
}//tacticode
