#include "Configuration.hpp"

namespace tacticode{
namespace utils{
	Configuration::Configuration() {
		_value = std::make_shared<Json::Value>();
	}

	file::JsonValue Configuration::value(){		
		return file::JsonValue(*_value);
	}

}//utils
}//tacticode
