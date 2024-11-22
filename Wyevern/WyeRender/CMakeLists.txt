
if("${Wyevern_Platform}" STREQUAL "Windows" OR "${Wyevern_Platform}" STREQUAL "UNIX")
    # Enable platforms for Windows and Unix (Vulkan, OpenGL)
	add_subdirectory(OpenGL)
endif()

if("${Wyevern_Platform}" STREQUAL "Windows")
	# Enable platforms for Windows only (Direct3D)
	
endif()
