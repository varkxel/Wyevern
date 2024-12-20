cmake_minimum_required(VERSION 3.30)

project(Wyevern_SDLCommon)

add_subdirectory(SDL)

add_library(Wyevern_SDLCommon SDLCommon.hpp SDLCommon.cpp)

target_link_libraries(Wyevern_SDLCommon PUBLIC SDL3::SDL3)
target_include_directories(Wyevern_SDLCommon PUBLIC SDL/include)
