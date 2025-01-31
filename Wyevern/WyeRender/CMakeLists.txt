cmake_minimum_required(VERSION 3.30)

project(Wyevern_Renderer)

add_library(Wyevern_Renderer
	"Renderer.hpp" "Renderer.cpp"
	"Windowing.hpp"
)
set_target_properties(Wyevern_Renderer PROPERTIES LINKER_LANGUAGE CXX)

function(Wyevern_AddRenderer rendererProject)
	target_include_directories(${rendererProject} PRIVATE "${Wyevern_SOURCE_DIR}")
	target_link_libraries(${rendererProject} PRIVATE Wyevern_Renderer)
endfunction()

add_subdirectory(OpenGL)
