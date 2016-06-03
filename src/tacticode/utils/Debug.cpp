#include "Debug.hpp"

namespace tacticode{
namespace utils{
namespace Debug{
	/* *******************************************************************
	 * Use << chain to add logs
	 * Use endl as end of a log
	 * ******************************************************************/	        
	std::ostream & NewLog() {
		return std::cerr;
	}
}//Debug
}//utils
}//tacticode