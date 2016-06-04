#pragma once

#include "Wrapper.hpp"
#include "v8/include/v8.h"

/* *******************************************************************
 * A wrapper class of v8 context
 * ******************************************************************/        

namespace tacticode{
namespace script{

class Context : public Wrapper< v8::Handle<v8::Context> >  {
public:
	Context(v8::Isolate *isolate);
	Context(Context const& c);
	Context& operator=(Context const& c);
	~Context();
};

}//script
}//tacticode