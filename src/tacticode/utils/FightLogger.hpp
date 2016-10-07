#pragma once

#include "json/json.h"
#include <memory>
#include <string>

namespace tacticode {
namespace utils{

		/*
		** Basically using Json::Value from Json cpp
		** allow easily add nested values
		** and log class
		*/
		class Log;
		//Later this Log needs to be refactor to be centralized through a factory
		class Log {
			std::shared_ptr<Json::Value> m_value;
		public:			
			Log();
			Json::Value& value() const;
			static Log Entity(int id, int x, int y, std::string const& breed,
				int team, int health, std::string const& name);
			static Log Action(int id, int x, int y, std::string const& type);
			static Log Action(int id, std::string const& type);

			template<typename T>
			void add(std::string const& key, T const& v) {
				value()[key] = (Json::Value(v));
			}
		};

		template<>
		void Log::add<Log>(std::string const& key, Log const& v);

		class FightLogger {
		public:
			Json::Value log;
			FightLogger();

			//more like intern use
			void addTurn(int turn);
			void addEntity(Log const &); //order is not important
			void addAction(Log const &); //order is important!
			void setWinner(int winnerid);
			void setFightId(int fightId);
			void setMap(std::string const&);
			//and more
			Json::Value& value();			

			~FightLogger();
		};

}//utils
}//tacticode