#pragma once

#include <v8.h>

/* *******************************************************************
 * A wrapper of v8::Function
 * ******************************************************************/
        
namespace tacticode{
namespace script{
namespace api{
	class AFunction : public Wrapper<v8::Handle<v8::Function> >
	{
	public:
		AFunction();
	};
}//
}//script
}//tacticode