#pragma once

#include <string>
#include <vector>

#include "IValue.hpp"
#include "jsoncpp/json/json.h"

namespace tacticode
{
	namespace file
	{
		class JsonValue : public IValue
		{
		private:
			static const std::string ENCODING;

		public:
			explicit JsonValue(const Json::Value& value);
			virtual ~JsonValue() {}

			virtual std::shared_ptr<IValue> clone() const;

			virtual bool hasField(const std::string& field) const;
			virtual std::vector<std::string> fieldNames() const;
			virtual size_t size() const;

			virtual bool isString() const;
			virtual bool isObject() const;
			virtual bool isBool() const;
			virtual bool isNumeric() const;
			virtual bool isArray() const;

			virtual std::string asString() const;
			virtual int asInt() const;
			virtual float asFloat() const;
			virtual bool asBool() const;

			virtual std::string getString(const std::string& field,
				const std::string& defaultValue = "") const;

			virtual int getInt(const std::string& field,
				int defaultValue = 0) const;

			virtual bool getBool(const std::string& field,
				bool defaultValue = false) const;

			virtual float getFloat(const std::string& field,
				float defaultValue = 0.0f) const;

			virtual engine::Vector2i getVector2i(const std::string& field,
				int defaultX = 0, int defaultY = 0) const;

			virtual engine::Vector2f getVector2f(const std::string& field,
				float defaultX = 0.0f, float defaultY = 0.0f) const;

			virtual std::shared_ptr<IValue> operator[](const std::string& field) const;
			virtual std::shared_ptr<IValue> operator[](size_t index) const;
			//to add set for later
			//virtual void set(std::string const&, IValue const&)
			private:
				Json::Value _value;
		};
	} // namespace file
} // namespace tacticode
