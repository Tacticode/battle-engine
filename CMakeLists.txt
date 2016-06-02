cmake_minimum_required (VERSION 3.1)
project(battle-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
option (TODO 
  "Enable todo debugging" ON)
include(cmake/Config.cmake)

#TODO handle v8 dependency using cmake
#include(CMakeLists-ExternalV8.txt)
			

include_directories("${PROJECT_SOURCE_DIR}/src")

#Later move jsoncpp to lib or whatever
include_directories("${PROJECT_SOURCE_DIR}/src/jsoncpp")


#Find V8
IF(NOT V8_DIR)
	set(V8_DIR "${PROJECT_SOURCE_DIR}/3rdparty/v8")
ENDIF (NOT V8_DIR)

MESSAGE(STATUS "Looking for v8 in ${V8_DIR}")

find_package(V8 REQUIRED)

IF (V8_FOUND)
MESSAGE(STATUS "V8 found  " ${V8_FOUND})
MESSAGE(STATUS "V8 include:  " ${V8_INCLUDE_DIR})
MESSAGE(STATUS "V8 library:  " ${V8_LIBRARY})

ELSE (V8_FOUND)
	MESSAGE( FATAL_ERROR "Please configure v8 to continue compile" )
ENDIF(V8_FOUND)


## Find Boost Unit.test framework
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#find_package(GMock REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

if(UNIX)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
	if(COMPILER_SUPPORTS_CXX14)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	else(COMPILER_SUPPORTS_CXX14)
	    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
	endif(COMPILER_SUPPORTS_CXX14)
endif(UNIX)

include_directories(3rdparty)
include_directories(3rdparty/v8/include)
add_executable(BattleEngine src/main.cpp)


if (WIN32)
	target_link_libraries(BattleEngine winmm)
	file(COPY
		${V8_ICUDATA_LIBRARY}
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
	target_link_libraries (BattleEngine ${V8_LIBRARY} "pthread")
ELSE (WIN32)
	SET(LDFLAGS -Wl,--start-group ${V8_LIBRARY} ${V8_ICUDATA_LIBRARY} -Wl,--end-group -lrt -ldl -pthread)
	target_link_libraries (BattleEngine ${LDFLAGS})
ENDIF(WIN32)

file(COPY
    ${V8_BLOB}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

include_relative_list(src)
