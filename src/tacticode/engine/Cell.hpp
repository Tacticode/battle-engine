#pragma once

namespace tacticode
{
	namespace engine
	{
		class Cell
		{
		public:
			const size_t x;
			const size_t y;
			const size_t height;

			Cell(size_t x_, size_t y_, size_t height_); // implicit
		};
	}
}