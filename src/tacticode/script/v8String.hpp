#pragma once

/* *******************************************************************
 * wrapper to construct v8 string easily
 * default encode utf-8
 * ******************************************************************/
#include <string>
#include "Wrapper.hpp"
#include "v8/include/v8.h"

namespace tacticode{
namespace script{


class v8String : public Wrapper<v8::Handle<v8::String> >
{
public:
	/* *******************************************************************
	 * carefult constructor not definitely exception safe
	 * ******************************************************************/	        
	v8String(std::string const& str);
	~v8String();	
};

}//script
}//tacticode