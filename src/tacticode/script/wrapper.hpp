#pragma once

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
	Wrapper(T resource) : _resource(resource) {}
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

