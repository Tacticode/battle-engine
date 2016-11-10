#pragma once

#include "ISpell.hpp"
#include "tacticode/engine/Map.hpp"
#include <memory>
#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/engine/Cell.hpp"

namespace tacticode
{
	namespace spell
	{
		class TrapSpell : public ISpell
		{
		protected:
		public:
			TrapSpell();
			virtual ~TrapSpell() = default;
			void castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine);
		};

		
	}
}
