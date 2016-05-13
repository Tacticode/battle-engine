#include <stdexcept>

#include "JsonValue.hpp"

namespace tacticode
{
	namespace file
	{
		const std::string JsonValue::ENCODING = "UTF-8";

		JsonValue::JsonValue(const Json::Value& value)
			: _value(value)
		{
		}

		std::shared_ptr<IValue> JsonValue::clone() const
		{
			return std::make_shared<JsonValue>(_value);
		}

		bool JsonValue::hasField(const std::string& field) const
		{
			return _value.isMember(field);
		}

		std::vector<std::string> JsonValue::fieldNames() const
		{
			return _value.getMemberNames();
		}

		size_t JsonValue::size() const
		{
			return _value.size();
		}

		bool JsonValue::isString() const
		{
			return _value.isString();
		}

		bool JsonValue::isObject() const
		{
			return _value.isObject();
		}

		bool JsonValue::isNumeric() const
		{
			return _value.isNumeric();
		}

		bool JsonValue::isArray() const
		{
			return _value.isArray();
		}

		std::string JsonValue::asString() const
		{
			return _value.asString();
		}

		bool JsonValue::asBool() const
		{
			return _value.asBool();
		}

		int JsonValue::asInt() const
		{
			return _value.asInt();
		}

		float JsonValue::asFloat() const
		{
			return _value.asFloat();
		}

		std::string JsonValue::getString(const std::string& field,
			const std::string& defaultValue) const
		{
			if (_value.isMember(field))
				return _value.get(field, ENCODING).asString();
			return defaultValue;
		}

		int JsonValue::getInt(const std::string& field,
			int defaultValue) const
		{
			if (_value.isMember(field))
				return _value.get(field, ENCODING).asInt();
			return defaultValue;
		}

		bool JsonValue::getBool(const std::string& field,
			bool defaultValue) const
		{
			if (_value.isMember(field))
				return _value.get(field, ENCODING).asBool();
			return defaultValue;
		}

		float JsonValue::getFloat(const std::string& field,
			float defaultValue) const
		{
			if (_value.isMember(field))
				return _value.get(field, ENCODING).asFloat();
			return defaultValue;
		}

		engine::Vector2i JsonValue::getVector2i(const std::string& field,
			int defaultX, int defaultY) const
		{
			if (hasField(field))
			{
				auto subfield = (*this)[field];
				if (subfield->isArray() && subfield->size() == 2)
				{
					engine::Vector2i result;
					result.x = (*subfield)[0]->asInt();
					result.y = (*subfield)[1]->asInt();
					return result;
				}
			}
			return engine::Vector2i(defaultX, defaultY);
		}

		engine::Vector2f JsonValue::getVector2f(const std::string& field,
			float defaultX, float defaultY) const
		{
			if (hasField(field))
			{
				auto subfield = (*this)[field];
				if (subfield->isArray() && subfield->size() == 2)
				{
					engine::Vector2f result;
					result.x = (*subfield)[0]->asFloat();
					result.y = (*subfield)[1]->asFloat();
					return result;
				}
			}
			return engine::Vector2f(defaultX, defaultY);
		}

		std::shared_ptr<IValue> JsonValue::operator[](const std::string& field) const
		{
			if (!hasField(field))
				throw std::runtime_error("Tried to get the non-existing field `" +
					field + "'");
			return std::make_shared<JsonValue>(_value[field]);
		}

		std::shared_ptr<IValue> JsonValue::operator[](size_t index) const
		{
			if (index >= size())
				throw std::runtime_error("Tried to get the non-existing index `" +
					std::to_string(index) + "'");
			return std::make_shared<JsonValue>(_value[static_cast<int>(index)]);
		}
	} // namespace file
} // namespace tacticode
