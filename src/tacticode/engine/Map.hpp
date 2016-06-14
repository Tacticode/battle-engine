#pragma once

#include <vector>
#include <memory>

#include "Cell.hpp"

namespace tacticode
{
	namespace file
	{
		class IValue;
	}

	namespace engine
	{
		class Map
		{
			using Row = std::vector<std::unique_ptr<Cell>>;
			using Field = std::vector<Row>;

			Field       m_field;
			int         m_width;
			int         m_height;
			std::string m_name;

			void deserialize(const file::IValue& json);

		public:
			static const int fieldOfViewHeightLimit;
			static const int moveHeightLimit;

			explicit Map(const file::IValue& json);

			int getWidth() const;
			int getHeight() const;
			
			Cell &       getCell(int x, int y);
			const Cell & getCell(int x, int y) const;

			bool isCellFree        (int x, int y) const;
			bool isCellAccessible  (int x, int y) const;
			bool hasCellLineOfSight(int x, int y) const;

			// Bresenham's line algorithm
			bool hasCellLineOfSightOnCell(int originX, int originY, int targetX, int targetY) const;
			std::stack<Cell &> shortestWayToCell(int originX, int originY, int targetX, int targetY);
		};
	}
}
