
if(UNIX)
	add_subdirectory(X11)
	add_subdirectory(Wayland)
elseif(WIN32)
	add_subdirectory(Windows)
endif()
