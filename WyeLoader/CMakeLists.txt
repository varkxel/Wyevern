
include("../Wyevern.cmake")

set(WyeLoader_WEXPath "" CACHE STRING "Set this to automatically load the specified path as the game module library.")
if(NOT WyeLoader_WEXPath STREQUAL "")
	set(WyeLoader_WEXPath_Set ON)
else()
	set(WyeLoader_WEXPath_Set OFF)
endif()

add_executable(WyeLoader
	"WyeLoader.cpp"
)
WyevernExport(WyeLoader)

if(${WyeLoader_WEXPath_Set})
	target_compile_definitions(WyeLoader PRIVATE WyeLoader_WEX_Path="${WyeLoader_WEXPath}")
endif()

target_link_libraries(WyeLoader PRIVATE Wyevern)
target_include_directories(WyeLoader PRIVATE ${Wyevern_SOURCE_DIR})
