include("${CMAKE_SOURCE_DIR}/Wyevern.cmake")

project(Wyevern_OpenGL LANGUAGES CXX VERSION ${Wyevern_Version})

if("${Wyevern_Platform}" STREQUAL "${Wyevern_Platform_UNIX}" OR "${Wyevern_Platform}" STREQUAL "${Wyevern_Platform_Windows}")
	message("OpenGL available")
	
	option(Wyevern_OpenGL_Enabled "Enables the OpenGL renderer for build." ON)
	
	if(${Wyevern_OpenGL_Enabled})
		message("OpenGL enabled")
		
		add_library(Wyevern_OpenGL
			"GLRenderer.hpp"
		)
		set_target_properties(Wyevern_OpenGL PROPERTIES LINKER_LANGUAGE CXX)
		Wyevern_AddRenderer(Wyevern_OpenGL)
		
		Wyevern_SDLCommon_Include(Wyevern_OpenGL)
	else()
		message("OpenGL disabled")
	endif()
else()
	message("OpenGL not available")
endif()
