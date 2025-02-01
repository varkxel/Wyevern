#ifndef WYEVERN_PLATFORM_INCLUDED
#define WYEVERN_PLATFORM_INCLUDED

#include <vector>

#include "Module.hpp"
#include "WyeRender/Renderer.hpp"

namespace Wyevern {
	struct Platform {
		std::shared_ptr<Module<Rendering::Renderer>> renderer;
	};
}

#endif
