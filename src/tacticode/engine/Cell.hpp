#pragma once

#include "tacticode/file/IValue.hpp"

namespace tacticode
{
	namespace engine
	{
		class Character;
		class Cell
		{
			int     m_x;
			int     m_y;
			int     m_height;
			bool    m_accessible;
			bool    m_lineOfSight;
			bool    m_isFree;
			int32_t m_characterId;

		public:
			Cell(int x, int y);
			Cell(const file::IValue& json);
			
			int    getX()      const;
			int    getY()      const;
			int    getHeight() const;

			int32_t getCharacterId() const;
			void    setCharacterId(int32_t characterId);
			void    unsetCharacterId();

			bool   isAccessible()   const;
			bool   isFree()         const;
			bool   hasLineOfSight() const;
		};
	}
}