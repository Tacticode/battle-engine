#pragma once

#include <vector>
#include <memory>
#include <stack>
#include <tuple>
#include <algorithm>

#include "Cell.hpp"
#include "Character.hpp"

namespace tacticode
{
	namespace file
	{
		class IValue;
	}

	namespace engine
	{
		class TrapEntity {
		public:
			virtual void trap(Character &) = 0;
			virtual ~TrapEntity() {}
		};

		class Map
		{
			using Row = std::vector<std::shared_ptr<Cell> >;
			using Field = std::vector<Row>;

			Field       m_field;
			int         m_width;
			int         m_height;
			std::string m_name;

			std::vector<engine::Vector2i> m_startingPositions;

			void deserialize(const file::IValue& json);

			//traps
			std::map<std::pair<int,int>, TrapEntity*> m_traps;

		public:
			static const int fieldOfViewHeightLimit;
			static const int moveHeightLimit;

			explicit Map(const file::IValue& json);

			int getWidth() const;
			int getHeight() const;
			
			Cell &       getCell(int x, int y);
			const Cell & getCell(int x, int y) const;
			Cell &       getCell(const Vector2i & position);
			const Cell & getCell(const Vector2i & position) const;
			Vector2i     getStartingPosition(int32_t index) const;

			std::shared_ptr<Cell> getManagedCell(int x, int y);

			bool isCellFree        (int x, int y) const;
			bool isCellFree        (const Vector2i & position) const;
			bool isCellAccessible  (int x, int y) const;
			bool isCellAccessible  (const Vector2i & position) const;
			bool hasCellLineOfSight(int x, int y) const;
			bool hasCellLineOfSight(const Vector2i & position) const;
			bool isCellOnMap       (int x, int y) const;
			bool isCellOnMap       (const Vector2i & position) const;

			bool moveCharacterToCell(Character & character, const Vector2i & position);

			bool addTrap(const Vector2i &position, TrapEntity *);

			// Bresenham's line algorithm
			bool hasCellLineOfSightOnCell(int originX, int originY, int targetX, int targetY) const;
			std::stack<std::shared_ptr<Cell>> shortestWayToCell(int originX, int originY, int targetX, int targetY);
		};
	}
}
