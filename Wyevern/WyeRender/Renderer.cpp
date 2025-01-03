#include "Renderer.hpp"

#include <vector>
#include <optional>

using namespace Wyevern::Rendering;

std::vector<std::optional<std::unique_ptr<Window>>> windows;

WindowID Renderer::CreateWindow() {
	WindowID nextID = 0;
	for(const std::optional<std::unique_ptr<Window>>& window : windows) {
		if(!window.has_value()) {
			break;
		}
		nextID += 1;
	}

	std::unique_ptr<Window> window = WindowConstructor();
	if(nextID == windows.size()) {
		windows.push_back(std::move(window));
	} else {
		windows[nextID] = std::move(window);
	}
	return nextID;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Renderer::DestroyWindow(const WindowID id) {
	windows[id] = std::nullopt;
}
