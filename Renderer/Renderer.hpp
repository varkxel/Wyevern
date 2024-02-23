#ifndef WYEVERN_RENDERER_INCLUDED
#define WYEVERN_RENDERER_INCLUDED

#include <string>

namespace Wyevern::Rendering {
	class Renderer {
	public:
		virtual ~Renderer() = 0;

		typedef int Window;
		virtual Window CreateWindow(int width, int height, const std::string& title) = 0;
		virtual void DestroyWindow(Window window);
	};
}

#endif
