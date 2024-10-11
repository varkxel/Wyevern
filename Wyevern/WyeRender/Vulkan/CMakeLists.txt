project(Wyevern_Vulkan LANGUAGES CXX VERSION ${Wyevern_Version})

include("${Wyevern_SOURCE_DIR}/SDLCommon.cmake")

find_package(Vulkan)

add_library(Wyevern_Vulkan VulkanRenderer.hpp VulkanPC.cpp)

Wyevern_Include_SDLCommon(Wyevern_Vulkan)
