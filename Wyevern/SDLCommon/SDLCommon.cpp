#include "SDLCommon.hpp"

#include <atomic>

#include <SDL3/SDL_init.h>

using namespace Wyevern::SDLCommon;

std::atomic<std::size_t> VideoInstanceCount = 0;

int Video::InstanceCount() {
	return VideoInstanceCount.load(std::memory_order_relaxed);
}

std::optional<std::string> Video::Init() {
	const std::size_t instanceCount = VideoInstanceCount.fetch_add(1, std::memory_order_relaxed);
	if(instanceCount > 0) {
		return std::nullopt;
	}

	const bool sdlResult = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if(!sdlResult) {
		return std::string("SDL3 failed to initialise the video subsystem. Reason:\n")
			+ SDL_GetError();
	}

	return std::nullopt;
}

void Video::Terminate() {
	const std::size_t instanceCount = VideoInstanceCount.fetch_sub(1, std::memory_order_relaxed);
	if(instanceCount == 1) {
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
}
