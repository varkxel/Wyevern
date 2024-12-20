#ifndef WYEVERN_SDLCOMMON_INCLUDED
#define WYEVERN_SDLCOMMON_INCLUDED

#include <optional>
#include <string>

namespace Wyevern::SDLCommon {
	namespace Video {
		int InstanceCount();

		std::optional<std::string> Init();
		void Terminate();
	}
}

#endif
