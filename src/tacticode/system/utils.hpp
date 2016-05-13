#pragma once

#include <cassert>

//If todo flag defined, define todo macro
#ifdef TODO
	#define todo(m) do{if(todoenv)assert(!m);}while(false)
#else
	#define todo(expr) ((void) (0))
#endif

extern bool todoenv;