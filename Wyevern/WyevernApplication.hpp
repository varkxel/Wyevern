#ifndef WYEVERN_APPLICATION_INCLUDED
#define WYEVERN_APPLICATION_INCLUDED

#include "Module.hpp"
#include "WyeRender/Renderer.hpp"

#define Wyevern_Application_Entry_Function_Name WyevernAppStart
#define Wyevern_Application_Exit_Function_Name WyevernAppExit

#define Wyevern_Application_Entry(Type) \
	Wyevern_Module_Function Type* Wyevern_Application_Entry_Function_Name ()

#define Wyevern_Application_Entry_Logic(Type) \
	return new Type()

#define Wyevern_Application_Exit(Type) \
	Wyevern_Module_Function void Wyevern_Application_Exit_Function_Name(Type* instance)

#define Wyevern_Application_Exit_Logic() \
	delete instance

#define Wyevern_Application_Definition(Type) \
	Wyevern_Module_Functions_Start() \
		Wyevern_Application_Entry(Type) { \
			Wyevern_Application_Entry_Logic(Type); \
		} \
		Wyevern_Application_Exit(Type) { \
			Wyevern_Application_Exit_Logic(); \
		} \
	Wyevern_Module_Functions_End()

namespace Wyevern {
	class WyevernApplication {
	public:
		WyevernApplication();
		virtual ~WyevernApplication() = default;
	};
}

#endif
