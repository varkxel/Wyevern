include("${CMAKE_SOURCE_DIR}/Wyevern.cmake")

project(Wyevern_OpenGL LANGUAGES CXX VERSION ${Wyevern_Version})

add_subdirectory(glbinding)

add_library(Wyevern_OpenGL GLRenderer.hpp GLRenderer.cpp)

#Wyevern_Include_SDLCommon(Wyevern_OpenGL)
