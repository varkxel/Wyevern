include("../Wyevern.cmake")

project(Wyevern LANGUAGES CXX VERSION ${Wyevern_Version})

add_library(Wyevern SHARED
	"WyevernApplication.hpp"
	
	"Architecture.hpp"
	
	"JobSystem/JobQueue.hpp"
	"JobSystem/JobSystem.cpp" "JobSystem/JobSystem.hpp"
	"JobSystem/JobHandle.cpp" "JobSystem/JobHandle.hpp"
	"JobSystem/Job.hpp"
	
	"Module.hpp"
)
WyevernExport(Wyevern)

target_compile_features(Wyevern PUBLIC ${Wyevern_CXX_Version})

add_subdirectory(WyeMaths)
add_subdirectory(WyeRender)
add_subdirectory(SDLCommon)

add_link_options("stdc++exp")
add_link_options("stdc++_libbacktrace")

# Include base folder
target_include_directories(Wyevern PUBLIC ${Wyevern_SOURCE_DIR})

# Modules
target_link_libraries(Wyevern PUBLIC WyeMaths)

target_include_directories(Wyevern PUBLIC ${WyeMaths_SOURCE_DIR}/Include)
