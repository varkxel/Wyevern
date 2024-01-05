cmake_minimum_required(VERSION 3.25)

include("Global.cmake")

project(Wyevern LANGUAGES CXX VERSION ${Wyevern_Version})

# External Includes
add_subdirectory(SDL)
set(SDL2_INCLUDE_DIRS "${SDL2_BINARY_DIR}/include")

add_subdirectory(WyeGen)
add_subdirectory(WyeMaths)

add_executable(Wyevern
	"Global/Architecture.hpp"
	"Instance.cpp"
	"Window.cpp"
	"JobSystem/JobQueue.hpp"
	"JobSystem/JobSystem.cpp" "JobSystem/JobSystem.hpp"
	"JobSystem/JobHandle.hpp" "JobSystem/JobHandle.cpp"
	"JobSystem/Job.hpp"
)

# Include base folder
target_include_directories(Wyevern PUBLIC ${Wyevern_SOURCE_DIR})

target_link_libraries(Wyevern PRIVATE SDL2)
target_include_directories(Wyevern PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(Wyevern PUBLIC WyeMaths)

target_include_directories(Wyevern PUBLIC ${WyeMaths_SOURCE_DIR})
