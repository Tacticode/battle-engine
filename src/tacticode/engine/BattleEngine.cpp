#include "tacticode\file\IValue.hpp"

#include "BattleEngine.hpp"
#include "Character.hpp"

namespace tacticode
{
	namespace engine
	{
		BattleEngine::BattleEngine()
		{
		}

		void BattleEngine::loadJson(file::IValue& json)
		{

		}

		void BattleEngine::readOnStdin()
		{
			// TODO: get json on stdin
			//loadJson(json);
		}

		bool BattleEngine::isReady()
		{
			return false;
		}

		bool BattleEngine::round()
		{
			for (auto character : characters)
			{
				character->play();
				if (gameOver())
				{
					return false;
				}
			}
			return true;
		}

		bool BattleEngine::gameOver()
		{
			return false;
		}

		void BattleEngine::game()
		{
			while (round());
			//TODO: use datas created by gameOver();
		}
	}
}