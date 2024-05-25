cmake_minimum_required(VERSION 3.25)

include("Global.cmake")

project(Wyevern LANGUAGES CXX VERSION ${Wyevern_Version})

add_subdirectory(WyeGen)
add_subdirectory(WyeMaths)
add_subdirectory(WyeRender)

add_executable(Wyevern
	"Global/Architecture.hpp"
	"JobSystem/JobQueue.hpp"
	"JobSystem/JobSystem.cpp" "JobSystem/JobSystem.hpp"
	"JobSystem/JobHandle.hpp" "JobSystem/JobHandle.cpp"
	"JobSystem/Job.hpp"

	"Module.hpp"
)

# Include base folder
target_include_directories(Wyevern PUBLIC ${Wyevern_SOURCE_DIR})

# Modules
target_link_libraries(Wyevern PUBLIC WyeMaths)
target_include_directories(Wyevern PUBLIC ${WyeMaths_SOURCE_DIR})
