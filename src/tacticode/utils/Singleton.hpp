#pragma once

/* *******************************************************************
 * This serves as a client include file 
 * For external module, include this file directly prevent you from any problem
 * ******************************************************************/

#include <iostream>
#include <exception>

namespace tacticode {
namespace utils {

template<typename T>
class Singleton
{
public:
	static T* GetInstance();
	static void Destroy();

private:

	Singleton(Singleton const&){};
	Singleton& operator=(Singleton const&){};

protected:
	static T* m_instance;

	Singleton(){ m_instance = static_cast <T*> (this); };
	~Singleton(){ m_instance = 0; };
};

template<typename T>
T* Singleton<T>::m_instance = 0;

template<typename T>
T* Singleton<T>::GetInstance()
{
	if(!m_instance)
	{
		try{
		Singleton<T>::m_instance = new T();			
		} catch (std::exception &e){
			std::cerr << e.what() << std::endl;
		}
	}
	return m_instance;
}

template<typename T>
void Singleton<T>::Destroy()
{
	delete Singleton<T>::m_instance;
	Singleton<T>::m_instance = 0;
}

} //utils
} //tacticode