function(set_target_sources TARGET)
	set(_sources)
	foreach(source ${ARGN})
		list(APPEND _sources ${CMAKE_CURRENT_LIST_DIR}/${source})
	endforeach()

	target_sources(${TARGET} PRIVATE ${_sources})
endfunction()

function(include_relative_list TO_INCLUDE_DIR)
	include(${CMAKE_CURRENT_LIST_DIR}/${TO_INCLUDE_DIR}/CMakeLists.txt)
endfunction()
