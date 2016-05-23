#include "tacticode/file/IValue.hpp"
#include "tacticode/file/JsonLoader.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"
#include "Map.hpp"
#include "Cell.hpp"

namespace tacticode
{
	namespace engine
	{
		void Map::deserialize(const file::IValue & json)
		{
			if (!json.isObject())
			{
				throw file::error::InvalidConfiguration("map", "map field is not an object");
			}
			if (!json["width"])
			{
				throw file::error::InvalidConfiguration("map", "Map has no width");
			}
			if (!json["height"])
			{
				throw file::error::InvalidConfiguration("map", "Map has no height");
			}
			if (!json["width"]->isNumeric())
			{
				throw file::error::InvalidConfiguration("map", "width is not a number");
			}
			if (!json["height"]->isNumeric())
			{
				throw file::error::InvalidConfiguration("map", "height is not a number");
			}
			if (json["width"]->asInt() <= 0)
			{
				throw file::error::InvalidConfiguration("map", "width is not greater than 0");
			}
			if (json["height"]->asInt() <= 0)
			{
				throw file::error::InvalidConfiguration("map", "height is not greater than 0");
			}
			m_width = json["width"]->asInt();
			m_height = json["height"]->asInt();
			for (size_t y = 0; y < m_height; ++y)
			{
				m_cells.push_back(Row());
				for (size_t x = 0; x < m_width; ++x)
				{
					m_cells[y].push_back({x, y, 0}); // TODO: height instead of 0
				}
			}
		}

		Map::Map(const file::IValue& json)
		{
			deserialize(json);
		}
	}
}