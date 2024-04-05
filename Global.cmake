set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(Wyevern_Version 0.0.0)

set(Wyevern_Platform_Windows INTERNAL "Windows")
set(Wyevern_Platform_UNIX INTERNAL "UNIX")

if(WIN32)
	set(Wyevern_Platform ${Wyevern_Platform_Windows})
elseif(UNIX)
	set(Wyevern_Platform ${Wyevern_Platform_UNIX})
endif()
