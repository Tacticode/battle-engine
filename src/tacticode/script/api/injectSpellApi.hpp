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
	void injectSpellApi(std::shared_ptr<Context> context);
}//api
}//script
}//tacticode