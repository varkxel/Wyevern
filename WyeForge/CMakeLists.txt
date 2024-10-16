include("../Wyevern.cmake")

project(WyeForge LANGUAGES CXX VERSION ${Wyevern_Version})

set(WyeForge_Sources "WyeForge.hpp" "WyeForge.cpp")

AddWyevernApplication(WyeForge "${WyeForge_Sources}")
