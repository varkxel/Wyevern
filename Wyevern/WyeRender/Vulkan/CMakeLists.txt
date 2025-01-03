include("${CMAKE_SOURCE_DIR}/Wyevern.cmake")

project(Wyevern_Vulkan LANGUAGES CXX VERSION ${Wyevern_Version})

if("${Wyevern_Platform}" STREQUAL "${Wyevern_Platform_UNIX}" OR "${Wyevern_Platform}" STREQUAL "${Wyevern_Platform_Windows}")
	message("Vulkan available")
	
	option(Wyevern_Vulkan_Enabled "Enables the Vulkan renderer for build." ON)
	
	if(${Wyevern_Vulkan_Enabled})
		message("Vulkan enabled")
		
		add_library(Wyevern_Vulkan
			"VulkanRenderer.hpp" "VulkanRenderer.cpp"
			"VulkanWindowing.hpp"
		)
		Wyevern_AddRenderer(Wyevern_Vulkan)
		
		Wyevern_SDLCommon_Include(Wyevern_Vulkan)
	else()
		message("Vulkan disabled")
	endif()
else()
	message("Vulkan not available")
endif()
