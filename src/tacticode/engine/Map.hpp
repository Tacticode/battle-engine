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

			Field       m_cells;
			size_t      m_width;
			size_t      m_height;
			std::string m_name;

			void deserialize(const file::IValue& json);

		public:
			explicit Map(const file::IValue& json);

		};
	}
}
