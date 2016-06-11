#pragma once

#include "Wrapper.hpp"
#include "v8/include/v8.h"

/* *******************************************************************
 * A wrapper class of v8 context
 * ******************************************************************/        
#include <iostream>
namespace tacticode{
namespace script{

class Context : public Wrapper< v8::Handle<v8::Context> >  {
public:
	enum INDEX{
		BATTLE_ENGINE = 1
	};

	Context(v8::Isolate *isolate);
	template<typename T>
	inline void embed(int index, T *data) {
		_resource->SetAlignedPointerInEmbedderData(index, data);
	}
	template <typename T>
	inline T* retrieve(int index) {
		return reinterpret_cast<T*>(_resource->GetAlignedPointerFromEmbedderData(index));
	}
	~Context();
};

}//script
}//tacticode