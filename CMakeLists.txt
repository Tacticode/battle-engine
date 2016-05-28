cmake_minimum_required (VERSION 2.6)
project(battle-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
option (TODO 
  "Enable todo debugging" ON)
include(cmake/Config.cmake)
			
if(UNIX)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
	if(COMPILER_SUPPORTS_CXX14)
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	else()
	    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
	endif()
endif(UNIX)

include_directories("${PROJECT_SOURCE_DIR}/src")

#Later move jsoncpp to lib or whatever
include_directories("${PROJECT_SOURCE_DIR}/src/jsoncpp")

add_executable(BattleEngine src/main.cpp)
include_relative_list(src)

##Find V8
#IF(NOT V8_DIR)
#	set(V8_DIR "${CMAKE_SOURCE_DIR}/v8")
#ENDIF (NOT V8_DIR)
#find_package(V8 REQUIRED)

#IF (V8_FOUND)
# MESSAGE(STATUS "V8 found  " ${V8_FOUND})
# MESSAGE(STATUS "V8 include:  " ${V8_INCLUDE_DIR})
# MESSAGE(STATUS "V8 library:  " ${V8_LIBRARY})

# ELSE (V8_FOUND)
# 	MESSAGE( FATAL_ERROR "Please configure v8 to continue compile" )
# ENDIF(V8_FOUND)


## Find Boost Unit.test framework
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#find_package(GMock REQUIRED)
