#pragma once
#include <iostream>
/* *******************************************************************
 * This template is only for intern use
 * ******************************************************************/
namespace tacticode {
namespace script{

template <typename T>
class Wrapper {
protected:
	T _resource;
public:
	Wrapper() {}
	Wrapper(T resource) : _resource(resource) {}
	Wrapper(Wrapper const& wrapper) {
		_resource = wrapper._resource;
		std::cerr << "copied"<< std::endl;
	}
	Wrapper& operator=(Wrapper const& wrapper) {
		_resource = wrapper._resource; return *this;
	}
	T& get() {
		return _resource;
	}
	T const& get() const {
		return _resource;
	}
	/* *******************************************************************
	 * This destructer is not virtual, not for interface purpose!
	 * ******************************************************************/	        
	~Wrapper() {}
};

} //script
} //tacticode

