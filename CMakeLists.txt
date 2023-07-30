cmake_minimum_required(VERSION 3.25)

include(Global.cmake)

project(Wyevern LANGUAGES CXX VERSION ${Wyevern_Version})

add_subdirectory(WyeMaths)

add_executable(Wyevern JobSystem/JobSystem.cpp)

target_link_libraries(Wyevern PUBLIC WyeMaths)
