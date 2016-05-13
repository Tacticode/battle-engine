#include <fstream>
#include <stdexcept>

#include "JsonLoader.hpp"
#include "JsonValue.hpp"

namespace tacticode
{
	namespace file
	{
		JsonLoader::JsonLoader(std::istream &file){
			std::string fileContent((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());

			Json::Reader reader;
			Json::Value value;

			if (!reader.parse(fileContent, value))
			{
				throw std::runtime_error("Could not parse \n"
					+ reader.getFormattedErrorMessages());
			}

			_value = std::make_shared<JsonValue>(value);			
		}

		JsonLoader::JsonLoader(const std::string& filename)
		{
			std::ifstream file(filename);
			if (!file)
				throw std::runtime_error("Could not open file `" + filename + "'");

			std::string fileContent((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());

			Json::Reader reader;
			Json::Value value;

			if (!reader.parse(fileContent, value))
			{
				throw std::runtime_error("Could not parse `" + filename + "'\n"
					+ reader.getFormattedErrorMessages());
			}

			_value = std::make_shared<JsonValue>(value);
		}

		const IValue& JsonLoader::value() const
		{
			return *_value;
		}
	}
}
