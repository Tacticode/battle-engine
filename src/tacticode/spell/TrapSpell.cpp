#include "TrapSpell.hpp"
#include "tacticode/utils/utils.hpp"
#include "tacticode/engine/Character.hpp"
#include "tacticode/engine/BattleEngine.hpp"
#include <iostream>

namespace tacticode{

using engine::Vector2i;
namespace spell{
		class TrapEntityImpl : public engine::TrapEntity
		{
			engine::Character     *character;
			engine::BattleEngine  *engine;
			Vector2i			  m_pos;
		public:
			TrapEntityImpl(engine::Character *c, engine::BattleEngine *bt, Vector2i const& pos) 
			: character(c), engine(bt), m_pos(pos)
			{				
			}
			virtual void trap(engine::Character &enemy) {
				enemy.applyDamage(10);
				utils::Log action;
				action.add("type", "trap");
				action.add("state", "destroyed");
				action.add("x", m_pos.x);
				action.add("y", m_pos.y);
				utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
			}
			virtual ~TrapEntityImpl() {
				//this can be dangerous
			}
		};

		TrapSpell::TrapSpell() : ISpell("TRAP") {}

		void TrapSpell::castSpell(int32_t casterId, std::shared_ptr<engine::Cell> cell, engine::BattleEngine & engine){
			auto caster = engine.getCharacter(casterId);
			Vector2i pos(cell->getX(), cell->getY());

			ISpell::logCast(casterId, pos.x, pos.y);
			if (engine.getMap()->addTrap(pos, new TrapEntityImpl(&(*caster), &engine, pos))) {
				auto action = utils::Log::Action(casterId, "trap");
				action.add("state", "created");
				action.add("x", pos.x);
				action.add("y", pos.y);
				action.add("caster", casterId);
				utils::Singleton<utils::FightLogger>::GetInstance()->addAction(action);
			}
		}
}
}