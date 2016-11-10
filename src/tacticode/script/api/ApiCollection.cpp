#include "api_intern.hpp"

#include "tacticode/script/ScriptFactory.hpp"
#include "tacticode/utils/Singleton.hpp"
#include "tacticode/script/script_intern.hpp"
#include "tacticode/system/Vector2.hpp"

#include <sstream>
#include <iostream>
#include <cassert>

#include "tacticode/engine/BattleEngine.hpp"
#include "tacticode/engine/Character.hpp"
#include "tacticode/utils/FightLogger.hpp"
#include "tacticode/engine/Cell.hpp"
#include "tacticode/engine/Map.hpp"

using tacticode::utils::Singleton;
using tacticode::script::ScriptFactory;
using tacticode::script::v8String;
using tacticode::script::Context;

namespace {
	using namespace tacticode;

  void functionLog(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  if (args.Length() >= 1) {
		  v8::HandleScope scope(args.GetIsolate());
		  v8::Local<v8::Value> arg = args[0];
		  if (arg->IsString()) {
			  v8::String::Utf8Value value(arg);
			  std::cerr << *value << std::endl;
		  }
	  }
  }

  tacticode::engine::BattleEngineContext* getBattleContext(v8::Local<v8::Context>& context) {
	  auto battle = reinterpret_cast<tacticode::engine::BattleEngineContext*>(
		  context->GetAlignedPointerFromEmbedderData(Context::BATTLE_ENGINE));
	  assert(battle);
	  assert(battle->character);
	  return battle;
  }

  v8::Local<v8::Object> createV8Entity(v8::Isolate* isolate, engine::Character& character) {
	  v8::Local<v8::Object> result = v8::Object::New(isolate);
	  v8::Local<v8::Context> context = isolate->GetCurrentContext();

	  result->Set(context, v8String::fromString("id"), v8::Number::New(isolate, character.getId()));
	  result->Set(context, v8String::fromString("name"), v8String::fromString(character.getName()));
	  result->Set(context, v8String::fromString("x"), v8::Number::New(isolate, character.getPosition().x));
	  result->Set(context, v8String::fromString("y"), v8::Number::New(isolate, character.getPosition().y));
	  result->Set(context, v8String::fromString("team"), v8::Number::New(isolate, character.getTeamId()));
	  result->Set(context, v8String::fromString("race"), v8String::fromString(character.getBreedString()));
	  result->Set(context, v8String::fromString("health"), v8::Number::New(isolate, character.getCurrentHealth()));
	  result->Set(context, v8String::fromString("maxHealth"), v8::Number::New(isolate, character.getBaseAttributes().health));
	  result->Set(context, v8String::fromString("movement"), v8::Number::New(isolate, character.getCurrentMovementPoints()));
	  result->Set(context, v8String::fromString("maxMovement"), v8::Number::New(isolate, character.getBaseAttributes().movement));
	  
	  const auto& spells = character.getSpells();
	  auto spellsArray = v8::Array::New(isolate, spells->size());
	  size_t index = 0;
	  for (const std::string& spell : *spells) {
		  spellsArray->Set(index++, v8String::fromString(spell));
	  }
	  result->Set(context, v8String::fromString("skills"), spellsArray);

	  return result;
  }

  v8::Local<v8::Object> createV8Cell(v8::Isolate *isolate, engine::Cell const& cell){
	  v8::Local<v8::Object> result = v8::Object::New(isolate);
	  v8::Local<v8::Context> context = isolate->GetCurrentContext();

	  result->Set(context, v8String::fromString("x"), v8::Number::New(isolate, cell.getX()));
	  result->Set(context, v8String::fromString("y"), v8::Number::New(isolate, cell.getY()));
	  result->Set(context, v8String::fromString("height"), v8::Number::New(isolate, cell.getHeight()));
	  result->Set(context, v8String::fromString("isAccessible"), v8::Boolean::New(isolate, cell.isAccessible()));
	  result->Set(context, v8String::fromString("hasLineOfSight"), v8::Boolean::New(isolate, cell.hasLineOfSight()));
	  result->Set(context, v8String::fromString("isFree"), v8::Boolean::New(isolate, cell.isFree()));
		return result;
  }

  void functionGetCurrentEntity(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  v8::EscapableHandleScope scope(args.GetIsolate());
	  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

	  auto battle_context = getBattleContext(context);
	  auto character = battle_context->character;

	  v8::Local<v8::Object> entity = createV8Entity(args.GetIsolate(), *character);

	  args.GetReturnValue().Set(scope.Escape(entity));
  }

  void functionGetEntities(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  v8::EscapableHandleScope scope(args.GetIsolate());
	  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

	  auto battle_context = getBattleContext(context);
	  auto& characters = battle_context->engine->getCharacters();

	  v8::Local<v8::Array> list = v8::Array::New(args.GetIsolate(), characters.size());
	  for (size_t i = 0; i < characters.size(); ++i) {
		  list->Set(i, createV8Entity(args.GetIsolate(), *characters[i]));
	  }

	  args.GetReturnValue().Set(scope.Escape(list));
  }

  void functionGetEntityOnCell(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  v8::EscapableHandleScope scope(args.GetIsolate());
	  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

	  auto battle_context = getBattleContext(context);
	  auto engine = battle_context->engine;

	  if (args.Length() >= 2) {
		  v8::Local<v8::Value> argX = args[0];
		  v8::Local<v8::Value> argY = args[1];

		  if (argX->IsNumber() && argY->IsNumber()) {
			  int32_t x = static_cast<int32_t>(argX->ToNumber()->Value());
			  int32_t y = static_cast<int32_t>(argY->ToNumber()->Value());

			  auto character = engine->getCharacterOnCell(x, y);
			  if (character) {
				  v8::Local<v8::Object> entity = createV8Entity(args.GetIsolate(), *character);
				  args.GetReturnValue().Set(scope.Escape(entity));
				  return;
			  }
		  }
	  }
	  args.GetReturnValue().Set(scope.Escape(v8::Null(args.GetIsolate())));
  }

  void functionGetCell(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  v8::EscapableHandleScope scope(args.GetIsolate());
	  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

	  auto battle_context = getBattleContext(context);
	  auto map = battle_context->engine->getMap();

	  if (args.Length() >= 2) {
		  v8::Local<v8::Value> argX = args[0];
		  v8::Local<v8::Value> argY = args[1];

		  if (argX->IsNumber() && argY->IsNumber()) {
			  int32_t x = static_cast<int32_t>(argX->ToNumber()->Value());
			  int32_t y = static_cast<int32_t>(argY->ToNumber()->Value());

			  if (map->isCellOnMap(x, y)) {
				  auto const& cell = map->getCell(x, y);
				  auto result = createV8Cell(args.GetIsolate(), cell);

				  auto character = battle_context->engine->getCharacterOnCell(x, y);
				  if (character) {
					  result->Set(context, v8String::fromString("entity"), createV8Entity(args.GetIsolate(), *character));
				  } else {				  	
					  result->Set(context, v8String::fromString("entity"), v8::Null(args.GetIsolate()));
				  }

				  args.GetReturnValue().Set(scope.Escape(result));
				  return;
			  }
		  }
	  }
	  args.GetReturnValue().Set(scope.Escape(v8::Null(args.GetIsolate())));
  }

  void functionMoveToCell(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  v8::EscapableHandleScope scope(args.GetIsolate());
	  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

	  auto battle_context = getBattleContext(context);
	  auto character = battle_context->character;
	  bool rt = false;

	  if (args.Length() >= 2) {
		  v8::Local<v8::Value> argX = args[0];
		  v8::Local<v8::Value> argY = args[1];
		  if (argX->IsNumber() && argY->IsNumber()) {
			  int32_t x = static_cast<int32_t>(argX->ToNumber()->Value());
			  int32_t y = static_cast<int32_t>(argY->ToNumber()->Value());

			  rt = character->moveToCell(engine::Vector2i(x, y));
		  }
	  }
	  v8::Local<v8::Value> result = v8::Boolean::New(args.GetIsolate(), rt);
	  args.GetReturnValue().Set(scope.Escape(result));
  }

  void functionCast(const v8::FunctionCallbackInfo<v8::Value>& args) {
	  v8::EscapableHandleScope scope(args.GetIsolate());
	  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();

	  auto battle_context = getBattleContext(context);
	  auto character = battle_context->character;
	  bool rt = false;

	  if (args.Length() == 3) {
		  v8::Local<v8::Value> spell = args[0];
		  v8::Local<v8::Value> argX = args[1];
		  v8::Local<v8::Value> argY = args[2];
		  if (spell->IsString() && argX->IsNumber() && argY->IsNumber()) {
			  v8::String::Utf8Value utf8value(spell);
			  std::string spellName(*utf8value);
			  int32_t x = static_cast<int32_t>(argX->ToNumber()->Value());
			  int32_t y = static_cast<int32_t>(argY->ToNumber()->Value());

			  rt = character->castSpell(spellName, engine::Vector2i(x, y), *(battle_context->engine));
		  }
	  }
	  else if (args.Length() == 1) {
		  v8::Local<v8::Value> spell = args[0];
		  if (spell->IsString()) {
			  v8::String::Utf8Value utf8value(spell);
			  std::string spellName(*utf8value);
			  rt = character->castSpell(spellName, character->getPosition(), *(battle_context->engine));
		  }
	  }

	  v8::Local<v8::Value> result = v8::Boolean::New(args.GetIsolate(), rt);
	  args.GetReturnValue().Set(scope.Escape(result));
  }
}

namespace tacticode{
namespace script{
namespace api{

ApiCollection::ApiCollection() {
}

void ApiCollection::injectApi(std::shared_ptr<tacticode::script::Context> context) {
	v8::Isolate *isolate = Singleton<ScriptFactory>::GetInstance()->getEngine();

	auto global = context->get()->Global();

	global->Set(v8String::fromString("$log"), v8::Function::New(isolate, functionLog));
	global->Set(v8String::fromString("getCurrentEntity"), v8::Function::New(isolate, functionGetCurrentEntity));
	global->Set(v8String::fromString("getEntities"), v8::Function::New(isolate, functionGetEntities));
	global->Set(v8String::fromString("getEntityOnCell"), v8::Function::New(isolate, functionGetEntityOnCell));
	global->Set(v8String::fromString("getCell"), v8::Function::New(isolate, functionGetCell));

	global->Set(v8String::fromString("moveToCell"), v8::Function::New(isolate, functionMoveToCell));
	global->Set(v8String::fromString("cast"), v8::Function::New(isolate, functionCast));

}

ApiCollection::~ApiCollection() {
}
}//api
}//script
}//tacticode
