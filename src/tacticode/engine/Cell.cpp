#include "tacticode/file/error/InvalidConfiguration.hpp"
#include "Cell.hpp"

namespace tacticode
{
	namespace engine
	{
		Cell::Cell(const file::IValue& json)
		{
			if (!json.isObject())
			{
				throw file::error::InvalidConfiguration("cell", "item of cells is not an object");
			}
			if (!json.hasField("x"))
			{
				throw file::error::InvalidConfiguration("cell", "Cell has no x");
			}
			if (!json.hasField("y"))
			{
				throw file::error::InvalidConfiguration("cell", "Cell has no y");
			}
			if (!json.hasField("height"))
			{
				throw file::error::InvalidConfiguration("cell", "Cell has no height");
			}
			if (!json["x"]->isNumeric())
			{
				throw file::error::InvalidConfiguration("cell", "x is not a number");
			}
			if (!json["y"]->isNumeric())
			{
				throw file::error::InvalidConfiguration("cell", "y is not a number");
			}
			if (!json["height"]->isNumeric())
			{
				throw file::error::InvalidConfiguration("cell", "height is not a number");
			}
			if (json["x"]->asInt() < 0)
			{
				throw file::error::InvalidConfiguration("cell", "x cannot be negative");
			}
			if (json["y"]->asInt() < 0)
			{
				throw file::error::InvalidConfiguration("cell", "y cannot be negative");
			}
			if (json["height"]->asInt() < 0)
			{
				throw file::error::InvalidConfiguration("cell", "height cannot be negative");
			}
			m_x      = json["x"]     ->asInt();
			m_y      = json["y"]     ->asInt();
			m_height = json["height"]->asInt();

			if (!json.hasField("accessible"))
			{
				throw file::error::InvalidConfiguration("cell", "Cell has no 'accessible' state");
			}
			if (!json["accessible"]->isBool())
			{
				throw file::error::InvalidConfiguration("cell", "accessible is not a boolean");
			}
			m_accessible = json["accessible"]->asBool();

			if (!json.hasField("los"))
			{
				throw file::error::InvalidConfiguration("cell", "Cell has no 'los' state");
			}
			if (!json["los"]->isBool())
			{
				throw file::error::InvalidConfiguration("cell", "los is not a boolean");
			}
			m_lineOfSight = json["los"]->asBool();
		}

		size_t Cell::getX() const
		{
			return m_x;
		}

		size_t Cell::getY() const
		{
			return m_y;
		}
		size_t Cell::getHeight() const
		{
			return m_height;
		}
		bool Cell::isAccessible() const
		{
			return m_accessible;
		}
		bool Cell::hasLineOfSight() const
		{
			return m_lineOfSight;
		}
	}
}
