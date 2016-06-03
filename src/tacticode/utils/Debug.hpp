#pragma once

/* *******************************************************************
 * A useful namespace for various logging purpose
 * ******************************************************************/

#include <iostream>

namespace tacticode{
namespace utils{
namespace Debug{
	/* *******************************************************************
	 * Use << chain to add logs
	 * Use endl as end of a log
	 * ******************************************************************/	        
	std::ostream & NewLog();
}//Debug
}//utils
}//tacticode

#define DEBUG_LOG (tacticode::utils::Debug::NewLog() << __FILE__ << ":" << __LINE__ << " " << __func__ << ": ")