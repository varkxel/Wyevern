set(Wyevern_CXX_Version cxx_std_23)

set(Wyevern_Version 0.0.0)

set(Wyevern_Platform_Windows INTERNAL "Windows")
set(Wyevern_Platform_UNIX INTERNAL "UNIX")

if(WIN32)
	set(Wyevern_Platform ${Wyevern_Platform_Windows})
elseif(UNIX)
	set(Wyevern_Platform ${Wyevern_Platform_UNIX})
endif()

function(AddWyevernApplication Project Sources)
	add_library(${Project} SHARED ${Sources})
	target_include_directories(${Project} PUBLIC ${Wyevern_SOURCE_DIR})
endfunction()
