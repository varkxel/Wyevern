cmake_minimum_required(VERSION 3.25)

project(WyeGen LANGUAGES CXX VERSION ${Wyevern_Version})

set(WyeGen_Src WyeGen.hpp WyeGen.cpp)
add_library(WyeGen ${WyeGen_Src})
