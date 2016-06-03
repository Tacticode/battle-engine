#pragma once

#include <string>

namespace tacticode{
namespace engine{
	class ICharacterScript {
	public:
		virtual void setScript(std::string const& script) = 0;
		virtual void run() = 0;
		virtual ~ICharacterScript() {}
	};
}//engine
}//tacticode
