#include "Context.hpp"

#include "tacticode/utils/utils.hpp"
#include "script_intern.hpp"

namespace tacticode{
namespace script{
	/* *******************************************************************
	 * compile the script
	 * ******************************************************************/
	Script::Script(Context &context, std::string const& rawscript) {
		v8String script_str(rawscript);

		auto thing = v8::Script::Compile(context.get(), script_str.get());
		if (thing.IsEmpty())
		{
			v8String empty_str("");
			thing = v8::Script::Compile(context.get(), empty_str.get());
		}
		_resource = thing.ToLocalChecked();
	}

	void Script::run(std::shared_ptr<Context> context) {
		_resource->Run(context->get());
	}

	Script::~Script() {

	}

}//script
}//tacticode
