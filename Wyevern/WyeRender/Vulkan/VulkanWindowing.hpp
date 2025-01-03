#ifndef WYEVERN_RENDERER_VULKAN_WINDOWING_INCLUDED
#define WYEVERN_RENDERER_VULKAN_WINDOWING_INCLUDED

#include "WyeRender/Windowing.hpp"

namespace Wyevern::Rendering::Vulkan {
	class VulkanWindow final : Window {
	public:
		VulkanWindow();
		~VulkanWindow() override;
	};
}

#endif
