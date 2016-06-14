#pragma once

#include "tacticode/file/IValue.hpp"

namespace tacticode
{
	namespace engine
	{
		class Character;

		class Cell
		{
			int    m_x;
			int    m_y;
			int    m_height;
			bool   m_accessible;
			bool   m_lineOfSight;
			std::shared_ptr<Character> m_character;

		public:
			Cell(const file::IValue& json);
			
			int    getX          () const;
			int    getY          () const;
			int    getHeight     () const;

			std::shared_ptr<Character>       getCharacter();
			const std::shared_ptr<Character> getCharacter() const;

			bool   isAccessible  () const;
			bool   isFree()         const;
			bool   hasLineOfSight() const;
		};
	}
}