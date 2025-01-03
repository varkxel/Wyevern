#ifndef WYEVERN_RENDERER_INCLUDED
#define WYEVERN_RENDERER_INCLUDED

#include <string>
#include <memory>

#include "Windowing.hpp"

namespace Wyevern::Rendering {
	typedef std::size_t WindowID;

	class Renderer {
	public:
		virtual ~Renderer() = default;

		WindowID CreateWindow();
		void DestroyWindow(WindowID id);
	protected:
		virtual std::unique_ptr<Window> WindowConstructor() = 0;
	};
}

#endif
