cmake_minimum_required(VERSION 3.30)

project(WyeGen LANGUAGES CXX VERSION ${Wyevern_Version})

set(WyeGen_Src WyeGen.hpp WyeGen.cpp)
add_library(WyeGen ${WyeGen_Src})
