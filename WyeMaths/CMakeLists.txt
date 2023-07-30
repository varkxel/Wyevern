cmake_minimum_required(VERSION 3.25)

include(../Global.cmake)

project(WyeMaths LANGUAGES C CXX VERSION ${Wyevern_Version})

set(WyeMaths_SwizzleGen_Src VectorSwizzles.c)
add_executable(WyeMaths_SwizzleGen ${WyeMaths_SwizzleGen_Src})

add_custom_target(WyeMaths_SwizzleGen_Run
	COMMAND WyeMaths_SwizzleGen
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Generated"
	SOURCES ${WyeMaths_SwizzleGen_Src}
)

add_library(WyeMaths BasicTypes.hpp Vector.hpp
	Test.cpp)

add_dependencies(WyeMaths WyeMaths_SwizzleGen_Run)

# Bypass for CMake to force it to CXX if no CPP file is built
set_target_properties(WyeMaths PROPERTIES LINKER_LANGUAGE CXX)
