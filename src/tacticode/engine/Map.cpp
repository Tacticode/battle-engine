#include "tacticode/file/IValue.hpp"
#include "tacticode/file/JsonLoader.hpp"
#include "Map.hpp"
#include "Cell.hpp"

namespace tacticode
{
	namespace engine
	{
		void Map::deserialize(file::IValue & json)
		{
			m_width = 10; // TODO
			m_height = 10; // TODO
			for (size_t y = 0; y < m_height; ++y)
			{
				m_cells.push_back(Row());
				for (size_t x = 0; x < m_width; ++x)
				{
					m_cells[y].push_back({x, y, 0}); // TODO: height instead of 0
				}
			}
		}

		Map::Map(file::IValue& json)
		{
			deserialize(json);
		}
	}
}