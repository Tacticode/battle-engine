#include "FightLogger.hpp"
#include <iostream>

namespace tacticode{
namespace utils{
		Log::Log() {
			m_value = std::make_shared<Json::Value>(Json::objectValue);
		}

 		template<>
		void Log::add<Log>(std::string const& key, Log const& v)
		{
			value()[key].swap(v.value());
		}

		Json::Value& Log::value() const
		{
			return *m_value;
		}

		Log Log::Entity(int id, int x, int y, std::string const& breed, int team)
		{
			Log rt;

			rt.value()["id"] = (Json::Value(id));
			rt.value()["x"] = (Json::Value(x));
			rt.value()["y"] = (Json::Value(y));
			rt.value()["breed"] = (Json::Value(breed));
			rt.value()["team"] = (Json::Value(team));
			return rt;
		}

		Log Log::Action(int id, int x, int y, std::string const& type)
		{
			Log rt;

			rt.value()["entity"] = Json::Value(id);
			rt.value()["x"] = Json::Value(x);
			rt.value()["y"] = Json::Value(y);
			rt.value()["type"] = Json::Value(type);
			return rt;
		}

		Log Log::Action(int id, std::string const& type)
		{
			Log rt;

			rt.value()["entity"] = Json::Value(id);
			rt.value()["type"] = Json::Value(type);
			return rt;
		}

		FightLogger::FightLogger()
			: log(Json::objectValue)
		{
				log["fightId"] = Json::Value(1); //just say 1 for now
				log["winner"] = Json::Value(1);
				log["map"] = Json::Value("sample");
				log["entities"] = Json::Value(Json::arrayValue);
				log["actions"] = Json::Value(Json::arrayValue);
		}

		void FightLogger::addAction(Log const& l)
		{
			log["actions"][log["actions"].size()].swap(l.value());
		}

		void FightLogger::addEntity(Log const& l)
		{
			log["entities"][log["entities"].size()].swap(l.value());
		}

		void FightLogger::setWinner(int winnerId)
		{
			log["winner"] = Json::Value(winnerId);
		}

		void FightLogger::setFightId(int fightId)
		{
			log["fightId"] = Json::Value(fightId);
		}

		void FightLogger::setMap(std::string const& mapString)
		{
			log["map"] = Json::Value(mapString.c_str());
		}

		FightLogger::~FightLogger()
		{
			Json::FastWriter wt;
			std::cout << wt.write(log);
		}

}//utils
}//tacticode