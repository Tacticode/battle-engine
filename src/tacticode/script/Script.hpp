#pragma once

/* *******************************************************************
* Script wrapper
* ******************************************************************/
#include <string>
#include "Wrapper.hpp"
#include "v8/include/v8.h"
#include <memory>
/* *******************************************************************
* A wrapper class of v8 context
* ******************************************************************/

namespace tacticode{
	namespace script{

		class Context;
		class Script : public Wrapper< v8::Handle<v8::Script> >  {
		public:
			/* *******************************************************************
			* compile the script
			* careful, constructor not exception safe!
			* ******************************************************************/
			Script(Context& context, std::string const& rawscript);			
			void run(std::shared_ptr<Context> context);
			~Script();
		};

	}//script
}//tacticode