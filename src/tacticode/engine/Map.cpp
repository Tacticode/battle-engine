#include "tacticode/file/IValue.hpp"
#include "tacticode/file/JsonLoader.hpp"
#include "tacticode/file/error/InvalidConfiguration.hpp"
#include "Map.hpp"
#include "Cell.hpp"

namespace tacticode
{
	namespace engine
	{
		const int Map::fieldOfViewHeightLimit = 2;
		const int Map::moveHeightLimit        = 2;

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
			for (int y = 0; y < m_height; ++y)
			{
				m_field.push_back(Row());
				for (int x = 0; x < m_width; ++x)
				{
					m_field[y].push_back(nullptr);
				}
			}
			auto ptrCells = json["cells"];
			const auto & cells = *ptrCells;
			for (size_t i = 0; i < cells.size(); ++i)
			{
				auto _cells_i = cells[i];
				std::shared_ptr<Cell> ptr = std::make_shared<Cell>(*_cells_i);
				if (ptr->getX() >= m_width || ptr->getY() >= m_height)
				{
					throw file::error::InvalidConfiguration("map",
						"cell is out of bound: [" + std::to_string(ptr->getX()) + "," + std::to_string(ptr->getY()) + "]");
				}
				if (m_field[ptr->getY()][ptr->getX()] != nullptr)
				{
					throw file::error::InvalidConfiguration("map",
						"the same cell is defined twice: [" + std::to_string(ptr->getX()) + "," + std::to_string(ptr->getY()) + "]");
				}
				m_field[ptr->getY()][ptr->getX()] = std::move(ptr);
			}
			for (size_t y = 0; y < m_field.size(); ++y)
			{
				for (size_t x = 0; x < m_field[y].size(); ++x)
				{
					if (m_field[y][x] == nullptr) {
						m_field[y][x] = std::make_shared<Cell>(x, y);
					}
					if (m_field[y][x] == nullptr)
					{
						throw file::error::InvalidConfiguration("map",
							"a cell is not defined: [" + std::to_string(x) + "," + std::to_string(y) + "]");
					}
				}
			}
		}

		Map::Map(const file::IValue& json)
		{
			deserialize(json);
		}

		int Map::getWidth() const
		{
			return m_width;
		}

		int Map::getHeight() const
		{
			return m_height;
		}

		Cell & Map::getCell(int x, int y)
		{
			return *m_field[y][x];
		}

		const Cell & Map::getCell(int x, int y) const
		{
			return *m_field[y][x];
		}

		Cell & Map::getCell(const Vector2i & position)
		{
			return *m_field[position.y][position.x];
		}

		const Cell & Map::getCell(const Vector2i & position) const
		{
			return *m_field[position.y][position.x];
		}

		std::shared_ptr<Cell> Map::getCellPtr(int x, int y)
		{
			return m_field[y][x];
		}

		bool Map::isCellFree(int x, int y) const
		{
			return m_field[y][x]->isFree();
		}

		bool Map::isCellFree(const Vector2i & position) const
		{
			return isCellFree(position.x, position.y);
		}

		bool Map::isCellAccessible(int x, int y) const
		{
			return m_field[y][x]->isAccessible();
		}

		bool Map::isCellAccessible(const Vector2i & position) const
		{
			return isCellAccessible(position.x, position.y);
		}

		bool Map::hasCellLineOfSight(int x, int y) const
		{
			return m_field[y][x]->hasLineOfSight();
		}

		bool Map::hasCellLineOfSight(const Vector2i & position) const
		{
			return hasCellLineOfSight(position.x, position.y);
		}

		bool Map::isCellOnMap(int x, int y) const
		{
			if (0 <= y && x < m_width && 0 <= y && y < m_height)
			{
				return true;
			}
			return false;
		}

		bool Map::isCellOnMap(const Vector2i & position) const
		{
			return isCellOnMap(position.x, position.y);
		}

		bool Map::moveCharacterToCell(const Character & character, const Vector2i & position)
		{
			if (std::abs(position.x - character.getPosition().x) + std::abs(position.y - character.getPosition().y) != 1)
			{
				return false;
			}
			if (!isCellOnMap(position) || !isCellFree(position) || !isCellAccessible(position))
			{
				return false;
			}
			m_field[position.y][position.x]->setCharacterId(character.getId());
			return true;
		}

		// Bresenham's line algorithm
		bool Map::hasCellLineOfSightOnCell(int originX, int originY, int targetX, int targetY) const
		{
			int aX = originX < targetX ? originX : targetX;
			int bX = originX > targetX ? originX : targetX;
			int aY = originY < targetY ? originY : targetY;
			int bY = originY > targetY ? originY : targetY;
			int originHeight = m_field[aY][aX]->getHeight();
			int targetHeight = m_field[bY][bX]->getHeight();

			float deltaX = static_cast<float>(bX - aX);
			if (std::abs(deltaX) < 0.00001) // avoid division by zero
			{
				for (int y = aY; y <= bY; ++y)
				{
					if (!m_field[y][aX]->hasLineOfSight()
							|| originHeight + Map::fieldOfViewHeightLimit >= m_field[y][aX]->getHeight())
					{
						return false;
					}
				}
				return true;
			}
			float deltaY = static_cast<float>(bY - aY);
			float error = -1.0f;
			float deltaError = std::abs(deltaY / deltaX);
			int y = aY;
			for (int x = aX; x <= bX - 1; ++x)
			{
				// x/y on the way
				if (!m_field[y][x]->hasLineOfSight()
						|| originHeight + Map::fieldOfViewHeightLimit >= m_field[y][x]->getHeight())
				{
					return false;
				}
				error = error + deltaError;
				if (error >= 0.0f)
				{
					++y;
					error -= 1.0f;
				}
			}
			return true;
		}

		// Dijkstra algorithm
		std::stack<std::shared_ptr<Cell>> Map::shortestWayToCell(int originX, int originY, int targetX, int targetY)
		{
			auto path = std::stack<std::shared_ptr<Cell>>();
			// TODO
			return std::move(path);
		}
	}
}
