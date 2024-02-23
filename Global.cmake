set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(Wyevern_Version 0.0.0)

set(Wyevern_Platforms
	Unknown
	Windows
	Linux
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(Wyevern_Platform Windows)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(Wyevern_Platform Linux)
else()
	set(Wyevern_Platform Unknown)
endif()

set_property(CACHE Wyevern_Platform PROPERTY STRINGS ${Wyevern_Platforms})
