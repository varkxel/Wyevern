
include("../Wyevern.cmake")

set(WyeLoader_GamePath "" CACHE STRING "Set this to automatically load the specified path as the game module library.")
if(NOT WyeLoader_GamePath STREQUAL "")
	set(WyeLoader_GamePath_Set ON)
else()
	set(WyeLoader_GamePath_Set OFF)
endif()

add_executable(WyeLoader
	"WyeLoader.cpp"
)
WyevernExport(WyeLoader)

if(${WyeLoader_WEXPath_Set})
	target_compile_definitions(WyeLoader PRIVATE WyeLoader_GamePath="${WyeLoader_GamePath}${Wyevern_SharedExtension}")
endif()

target_link_libraries(WyeLoader PRIVATE Wyevern)
target_include_directories(WyeLoader PRIVATE ${Wyevern_SOURCE_DIR})
