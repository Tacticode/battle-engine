#pragma once

#include "tacticode/file/IValue.hpp"

namespace tacticode
{
	namespace engine
	{
		class Cell
		{
			size_t m_x;
			size_t m_y;
			size_t m_height;
			bool   m_accessible;
			bool   m_lineOfSight;

		public:
			Cell(const file::IValue& json);
			
			size_t getX          () const;
			size_t getY          () const;
			size_t getHeight     () const;

			bool   isAccessible  () const;
			bool   hasLineOfSight() const;
		};
	}
}