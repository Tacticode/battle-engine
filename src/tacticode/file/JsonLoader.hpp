#pragma once

#include <memory>
#include <iostream>
//#include "json/reader.h"
#include "json/json.h"

namespace tacticode
{
	namespace file
	{
		class IValue;

		class JsonLoader
		{
		public:
			JsonLoader(const std::string& filename);
			JsonLoader(std::istream &);
			const IValue& value() const;

		private:
			std::shared_ptr<IValue> _value;
		};
	}
}
