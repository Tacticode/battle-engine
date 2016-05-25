#pragma once

#include <memory>
#include <vector>

#include "tacticode/system/Vector2.hpp"

namespace tacticode
{
	namespace file
	{
		class IValue
		{
		public:
			virtual ~IValue() {}

			virtual std::shared_ptr<IValue> clone() const = 0;

			virtual bool hasField(const std::string& field) const = 0;
			virtual std::vector<std::string> fieldNames() const = 0;
			virtual size_t size() const = 0;

			virtual bool isString() const = 0;
			virtual bool isObject() const = 0;
			virtual bool isBool() const = 0;
			virtual bool isNumeric() const = 0;
			virtual bool isArray() const = 0;

			virtual std::string asString() const = 0;
			virtual int asInt() const = 0;
			virtual float asFloat() const = 0;
			virtual bool asBool() const = 0;

			virtual std::string getString(const std::string& field,
				const std::string& defaultValue = "") const = 0;

			virtual int getInt(const std::string& field,
				int defaultValue = 0) const = 0;

			virtual bool getBool(const std::string& field,
				bool defaultValue = false) const = 0;

			virtual float getFloat(const std::string& field,
				float defaultValue = 0.0f) const = 0;

			virtual engine::Vector2i getVector2i(const std::string& field,
				int defaultX = 0, int defaultY = 0) const = 0;

			virtual engine::Vector2f getVector2f(const std::string& field,
				float defaultX = 0.0f, float defaultY = 0.0f) const = 0;

			virtual std::shared_ptr<IValue> operator[](const std::string& field) const = 0;
			virtual std::shared_ptr<IValue> operator[](size_t index) const = 0;
		};
	} // namespace file
} // namespace tacticode
