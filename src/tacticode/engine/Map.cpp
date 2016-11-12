#include "tacticode/file/IValue.hpp"
#include "tacticode/file/JsonLoader.hpp"
#include "tacticode/file/JsonValue.hpp"
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
			if (!json.hasField("start_positions"))
			{
				throw file::error::InvalidConfiguration("map", "Map has no start_positions");
			}
			if (!json["start_positions"]->isArray())
			{
				throw file::error::InvalidConfiguration("map", "start_positions is not an array");
			}
			auto ptrStartPositions = json["start_positions"];
			for (size_t i = 0; i < ptrStartPositions->size(); ++i)
			{
				auto ptrStartPosition = (*ptrStartPositions)[i];
				if (!ptrStartPosition->hasField("x") || !ptrStartPosition->hasField("y"))
				{
					throw file::error::InvalidConfiguration("map", "start_positions should contain x and y");
				}
				auto ptrStartPositionX = (*ptrStartPosition)["x"];
				auto ptrStartPositionY = (*ptrStartPosition)["y"];
				if (!ptrStartPositionX->isNumeric() || !ptrStartPositionY->isNumeric())
				{
					throw file::error::InvalidConfiguration("map", "start_positions should contain two numbers");
				}
				engine::Vector2i v(ptrStartPositionX->asInt(), ptrStartPositionY->asInt());
				m_startingPositions.push_back(v);
			}
		}

		Map::Map(const file::IValue& json)
		{
			deserialize(json);			
			utils::Singleton<utils::FightLogger>::GetInstance()->value()["map"] = tacticode::file::getRawJsonValue(json);
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

		std::shared_ptr<Cell> Map::getManagedCell(int x, int y)
		{
			return m_field[y][x];
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

		Vector2i Map::getStartingPosition(int32_t index) const
		{
			return m_startingPositions[index];
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
			if (0 <= x && x < m_width && 0 <= y && y < m_height)
			{
				return true;
			}
			return false;
		}

		bool Map::isCellOnMap(const Vector2i & position) const
		{
			return isCellOnMap(position.x, position.y);
		}

		bool Map::moveCharacterToCell(Character & character, const Vector2i & position)
		{
			int32_t distance = std::abs(position.x - character.getPosition().x) + std::abs(position.y - character.getPosition().y);
			if (distance != 1 || character.getCurrentMovementPoints() < distance)
			{
				return false;
			}
			if (!isCellOnMap(position) || !isCellFree(position) || !isCellAccessible(position))
			{
				return false;
			}
			character.reduceCurrentMovementPoint(distance);
			m_field[character.getPosition().y][character.getPosition().x]->unsetCharacterId();
			m_field[position.y][position.x]->setCharacterId(character.getId());
			character.setPosition(position.x, position.y);
			return true;
		}

		int Map::getOctant(int x0, int y0, int x1, int y1) const
		{
			if (x0 < x1)
			{
				if (y0 > y1)
				{
					if (std::abs(x0 - x1) > std::abs(y0 - y1))
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					if (std::abs(x0 - x1) > std::abs(y0 - y1))
					{
						return 7;
					}
					else
					{
						return 6;
					}
				}
			}
			else
			{
				if (y0 > y1)
				{
					if (std::abs(x0 - x1) > std::abs(y0 - y1))
					{
						return 3;
					}
					else
					{
						return 2;
					}
				}
				else
				{
					if (std::abs(x0 - x1) > std::abs(y0 - y1))
					{
						return 4;
					}
					else
					{
						return 5;
					}
				}
			}
			return -1;
		}

		// Fix me
		bool Map::hasLineOfSightByOctant(int originX, int originY, int targetX, int targetY, int octant, int originHeight) const
		{
			int aX;
			int bX;
			int aY;
			int bY;

			switch (octant)
			{
			case 0:
				aX = originX;
				aY = originY;
				bX = targetX;
				bY = targetY;
				break;
			case 1:
				aX = originY;
				aY = originX;
				bX = targetY;
				bY = targetX;
				break;
			case 2:
				aX = targetY;
				aY = originX;
				bX = originY;
				bY = targetX;
				break;
			case 3:
				aX = targetX;
				aY = originY;
				bX = originX;
				bY = targetY;
				break;
			case 4:
				aX = targetX;
				aY = targetY;
				bX = originX;
				bY = originY;
				break;
			case 5:
				aX = targetY;
				aY = targetX;
				bX = originY;
				bY = originX;
				break;
			case 6:
				aX = targetY;
				aY = originX;
				bX = originY;
				bY = targetX;
				break;
			case 7:
				aX = originX;
				aY = targetY;
				bX = targetX;
				bY = originY;
				break;
			}
			if (!m_field[y][x]->hasLineOfSight()
				|| originHeight + Map::fieldOfViewHeightLimit >= m_field[y][x]->getHeight())
			{
				return false;
			}
			return false;
		}

		// Bresenham's line algorithm
		bool Map::hasCellLineOfSightOnCell(int originX, int originY, int targetX, int targetY) const
		{

			int octant = getOctant(originX, originY, targetX, targetY);

			int aX;
			int bX;
			int aY;
			int bY;

			switch (octant)
			{
			case 0:
				aX = originX;
				aY = originY;
				bX = targetX;
				bY = targetY;
				break;
			case 1:
				aX = originY;
				aY = originX;
				bX = targetY;
				bY = targetX;
				break;
			case 2:
				aX = originY;
				aY = targetX;
				bX = targetY;
				bY = originX;
				break;
			case 3:
				aX = targetX;
				aY = originY;
				bX = originX;
				bY = targetY;
				break;
			case 4:
				aX = targetX;
				aY = targetY;
				bX = originX;
				bY = originY;
				break;
			case 5:
				aX = targetY;
				aY = targetX;
				bX = originY;
				bY = originX;
				break;
			case 6:
				aX = originY;
				aY = targetX;
				bX = targetY;
				bY = originX;
				break;
			case 7:
				aX = originX;
				aY = targetY;
				bX = targetX;
				bY = originY;
				break;
			}


			int originHeight = m_field[aY][aX]->getHeight();
			int targetHeight = m_field[bY][bX]->getHeight();

			float deltaX = static_cast<float>(bX - aX);
			float deltaY = static_cast<float>(bY - aY);
			float error = -1.0f;
			float deltaError = std::abs(deltaY / deltaX);
			int y = aY;
			for (int x = aX; x <= bX - 1; ++x)
			{
				// x/y on the way
				if (!hasLineOfSightByOctant(x, y, octant, originHeight))
					//		{
					//			return false;
					//		}
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

			//consider store this within the class to avoid realloc
			int *visited = new int[m_width * m_height];
			for (int i = 0; i < m_width * m_height; i++) {
				visited[i] = 0;
			}
			// TODO
			delete []visited;
			return std::move(path);
		}
	}
}
