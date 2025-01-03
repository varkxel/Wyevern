#ifndef WYEVERN_RENDERER_VULKAN_INCLUDED
#define WYEVERN_RENDERER_VULKAN_INCLUDED

#include <WyeRender/Renderer.hpp>

namespace Wyevern::Rendering::Vulkan {
	class VulkanRenderer final : Renderer {
	protected:
		std::unique_ptr<Window> WindowConstructor() override;
	};
}

#endif
