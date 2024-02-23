#ifndef WYEVERN_RENDERER_VULKAN_INCLUDED
#define WYEVERN_RENDERER_VULKAN_INCLUDED

#include "Renderer/Renderer.hpp"
#include <SDL2/SDL.h>

namespace Wyevern::Rendering::Vulkan {
	class VulkanRenderer : Renderer {
		Window CreateWindow(int width, int height, const std::string& title) final;
		void DestroyWindow(Window window) final;
	};
}

#endif
