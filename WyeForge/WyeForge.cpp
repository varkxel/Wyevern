#include "WyeForge.hpp"

#include <Wyevern/Module.hpp>

#include <iostream>

Wyevern_Application_Definition(Wyevern::Editor::WyeForge)

#if false
Wyevern_Module_Functions_Start()
	Wyevern_Application_Entry(Wyevern::Editor::WyeForge) {
		Wyevern_Application_Entry_Logic(Wyevern::Editor::WyeForge);
	}

	Wyevern_Application_Exit(Wyevern::Editor::WyeForge) {
		Wyevern_Application_Exit_Logic();
	}
Wyevern_Module_Functions_End()
#endif

namespace Wyevern::Editor
{
	WyeForge::WyeForge()
	{
		std::cout << "loaded!" << std::endl;
	}
}
