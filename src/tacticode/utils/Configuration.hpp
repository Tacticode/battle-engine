#pragma once

/* *******************************************************************
 * A easy to use configuration class
 * ******************************************************************/
#include <memory>
#include "jsoncpp/json/json.h"
#include "tacticode/file/JsonValue.hpp"

namespace tacticode{
namespace utils{
class Configuration 
{
	std::shared_ptr<Json::Value> _value;

public:
	Configuration();
	file::JsonValue value();

	template<typename T>
	void set(std::string const& key, T const& v) {
		(*_value)[key] = (Json::Value(v));
	}
};

}//utils
}//tacticode
