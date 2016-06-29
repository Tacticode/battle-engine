#pragma once

#include <string>
#include <memory>
namespace tacticode{
namespace engine{
	class Character;
	class Team;
	class BattleEngine;
	/* *******************************************************************
	 * Structure to share between ia script and battle engine
	 * ******************************************************************/        
	struct BattleEngineContext {
		BattleEngine *engine;
		std::shared_ptr<Character> 	character;
		std::shared_ptr<Team> 			team;
		//Other info like battle engine
		//maintain raw pointers instead of use shared_ptr, making life easier
	};
	class ICharacterScript {
	public:
		virtual void setScript(std::string const& script) = 0;
		/* *******************************************************************
		 * You will need to maintain a BattleEngineContext
		 * ******************************************************************/
		virtual BattleEngineContext *getBattleEngineContext() = 0;
		virtual void run() = 0;
		virtual ~ICharacterScript() {}
	};
}//engine
}//tacticode
