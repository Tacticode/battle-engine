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
			if (!json.hasField("name"))
			{
				throw file::error::InvalidConfiguration("map", "map has no name");
			}
			if (!json["name"]->isString())
			{
				throw file::error::InvalidConfiguration("map", "name field is not a string");
			}
			m_name = json["name"]->asString();
			if (!json.hasField("width"))
			{
				throw file::error::InvalidConfiguration("map", "Map has no width");
			}
			if (!json.hasField("height"))
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
			if (!json.hasField("cells"))
			{
				throw file::error::InvalidConfiguration("map", "Map has no cells");
			}
			if (!json["cells"]->isArray())
			{
				throw file::error::InvalidConfiguration("map", "cells is not an array");
			}
			// initializing the Map before allow us to read an unordered "cells" array
			for (size_t y = 0; y < m_height; ++y)
			{
				m_cells.push_back(Row());
				for (size_t x = 0; x < m_width; ++x)
				{
					m_cells[y].push_back(nullptr);
				}
			}
			auto _cells = json["cells"];
			const auto & cells = *_cells;
			for (size_t i = 0; i < cells.size(); ++i)
			{
				auto _cells_i = cells[i];
				std::unique_ptr<Cell> ptr = std::make_unique<Cell>(*_cells_i);
				if (ptr->getX() >= m_width || ptr->getY() >= m_height)
				{
					throw file::error::InvalidConfiguration("map",
						"cell is out of bound: [" + std::to_string(ptr->getX()) + "," + std::to_string(ptr->getY()) + "]");
				}
				if (m_cells[ptr->getY()][ptr->getX()] != nullptr)
				{
					throw file::error::InvalidConfiguration("map",
						"the same cell is defined twice: [" + std::to_string(ptr->getX()) + "," + std::to_string(ptr->getY()) + "]");
				}
				m_cells[ptr->getY()][ptr->getX()] = std::move(ptr);
			}
		}

		Map::Map(const file::IValue& json)
		{
			deserialize(json);
		}
	}
}
