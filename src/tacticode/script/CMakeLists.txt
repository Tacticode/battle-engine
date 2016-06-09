set_target_sources(BattleEngine
	script_intern.hpp

	ScriptFactory.cpp
	ScriptFactory.hpp
	Context.hpp
	Context.cpp
	v8String.hpp
	v8String.cpp
	Script.hpp
	Script.cpp
	CharacterScript.hpp
	CharacterScript.cpp
	Wrapper.hpp
	)

include_relative_list(api)
