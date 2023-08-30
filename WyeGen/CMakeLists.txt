cmake_minimum_required(VERSION 3.25)

project(WyeGen LANGUAGES C VERSION ${Wyevern_Version})

set(WyeGen_Src WyeGen.h WyeGen.c)
add_library(WyeGen ${WyeGen_Src})
