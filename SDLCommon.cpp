#include "SDLCommon.hpp"

#include <stdexcept>

int sdlVideoInstances = 0;

void Wyevern::SDLCommon::InitVideo() {
	if(sdlVideoInstances++ > 0) {
		return;
	}

	const int sdlCode = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if(sdlCode < 0) {
		throw std::runtime_error(
			"SDL2 failed to initialise with error code " + std::to_string(sdlCode) + ":\n"
		+	std::string(SDL_GetError())
		);
	}
}

void Wyevern::SDLCommon::TerminateVideo() {
	if(--sdlVideoInstances > 0) {
		return;
	}
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
