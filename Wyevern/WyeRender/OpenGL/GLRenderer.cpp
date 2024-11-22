#include "GLRenderer.hpp"

#include <SDLCommon.hpp>
#include <SDL2/SDL_video.h>
#include <vector>
#include <stdexcept>

using namespace Wyevern::Rendering;
using namespace Wyevern::Rendering::Vulkan;

std::vector<SDL_Window*> windows;

Renderer::Window VulkanRenderer::CreateWindow(int width, int height, const std::string& title) {
	Wyevern::SDLCommon::InitVideo();

	SDL_Window* window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_VULKAN
	);

	if(window == nullptr) {
		throw std::runtime_error(
			"SDL2 Vulkan Window failed to be created.\nReason:\n"
		+	std::string(SDL_GetError())
		);
	}

	const int id = windows.size();
	windows.push_back(window);

	return id;
}

void VulkanRenderer::DestroyWindow(Renderer::Window window) {
	Wyevern::SDLCommon::TerminateVideo();
}
