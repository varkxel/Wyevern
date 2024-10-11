include("../Wyevern.cmake")

project(WyeForge LANGUAGES CXX VERSION ${Wyevern_Version})

AddWyevernApplication(WyeForge "WyeForge.hpp")
