#include "VulkanRenderer.hpp"

#include <SDLCommon/SDLCommon.hpp>
#include <SDL3/SDL.h>
#include <vector>
#include <stdexcept>

using namespace Wyevern::Rendering;
using namespace Wyevern::Rendering::Vulkan;

std::vector<SDL_Window*> windows;

Renderer::Window VulkanRenderer::CreateWindow(int width, int height, const std::string& title) {
	SDLCommon::Video::Init();

	SDL_Window* window = SDL_CreateWindow(
		title.c_str(),
		width, height,
		SDL_WINDOW_VULKAN
	);

	if(window == nullptr) {
		throw std::runtime_error(
			"SDL3 Vulkan Window failed to be created.\nReason:\n"
		+	std::string(SDL_GetError())
		);
	}

	const int id = windows.size();
	windows.push_back(window);

	return id;
}

void VulkanRenderer::DestroyWindow(Windowing window) {
	SDLCommon::Video::Terminate();
}
