#ifndef WYEVERN_EDITOR_INCLUDED
#define WYEVERN_EDITOR_INCLUDED

#include <Wyevern/WyevernApplication.hpp>

namespace Wyevern::Editor
{
	class WyeForge final : WyevernApplication
	{
	public:
		WyeForge();
		~WyeForge() override {}
	};
}

#endif
