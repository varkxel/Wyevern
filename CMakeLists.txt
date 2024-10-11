cmake_minimum_required(VERSION 3.25)

include("Wyevern.cmake")

project(WyevernEngine VERSION ${Wyevern_Version})

add_subdirectory(WyeGen)
add_subdirectory(Wyevern)
add_subdirectory(WyeLoader)

add_subdirectory(WyeForge)
