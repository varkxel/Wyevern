cmake_minimum_required(VERSION 3.25)

include("../../Wyevern.cmake")

project(WyeMaths LANGUAGES CXX VERSION ${Wyevern_Version})

set(WyeMaths_SwizzleGen_Src SwizzleGen.cpp)
add_executable(WyeMaths_SwizzleGen ${WyeMaths_SwizzleGen_Src})
target_include_directories(WyeMaths_SwizzleGen PRIVATE ${WyeGen_SOURCE_DIR})
target_link_libraries(WyeMaths_SwizzleGen PRIVATE WyeGen)
target_compile_features(WyeMaths_SwizzleGen PUBLIC ${Wyevern_CXX_Version})

file(MAKE_DIRECTORY "Generated")
add_custom_target(WyeMaths_SwizzleGen_Run
	COMMAND WyeMaths_SwizzleGen
	WORKING_DIRECTORY "${WyeMaths_SOURCE_DIR}/Generated"
	SOURCES ${WyeMaths_SwizzleGen_Src}
)

add_library(WyeMaths BasicTypes.hpp Vector.hpp VectorArray.hpp)
target_compile_features(WyeMaths PUBLIC ${Wyevern_CXX_Version})

add_dependencies(WyeMaths WyeMaths_SwizzleGen_Run)

# Bypass for CMake to force it to CXX if no CPP file is built
set_target_properties(WyeMaths PROPERTIES LINKER_LANGUAGE CXX)
