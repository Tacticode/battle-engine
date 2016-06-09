#pragma once

/* *******************************************************************
 * Maintains a collection of api call
 * Use the singleton to access
 * ******************************************************************/
#include <memory>
#include <map>
#include <unordered_map>
#include <v8.h>

namespace tacticode{
namespace script{
class Context;
namespace api{
	class AFunction;
	class ApiCollection
	{
		/* *******************************************************************
		 * This is unused for now
		 * ******************************************************************/		        
		std::unordered_map<std::string, v8::Handle<v8::Value> > _collection;
	public:
		ApiCollection();
		void injectApi(std::shared_ptr<Context> context);
		~ApiCollection();
	};
}//api
}//script
}//tacticode