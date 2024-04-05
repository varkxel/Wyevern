#ifndef WYEVERN_RENDERER_VULKAN_INCLUDED
#define WYEVERN_RENDERER_VULKAN_INCLUDED

#include "WyeRender/Renderer.hpp"

namespace Wyevern::Rendering::Vulkan {
	class VulkanRenderer final : Renderer {
		Window CreateWindow(int width, int height, const std::string& title) override;
		void DestroyWindow(Window window) override;


	};
}

#endif
