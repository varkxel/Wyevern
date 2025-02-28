#ifndef WYEVERN_MODULE_INCLUDED
#define WYEVERN_MODULE_INCLUDED

#include <string>
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <memory>

#define Wyevern_Module_Functions_Start() extern "C" {
#define Wyevern_Module_Functions_End() }

#ifdef WYEVERN_PLATFORM_WINDOWS
#define Wyevern_Module_Function __declspec(dllexport)
#elifdef WYEVERN_PLATFORM_UNIX
#define Wyevern_Module_Function /* Nothing is required. */
#else
#define Wyevern_Module_Function
#endif

namespace Wyevern {
	template<typename TModule>
	class Module {
	public:
		virtual ~Module() = default;

		TModule* Instance;
	};

	template<typename TModule, typename... Args>
	class StaticModule final : public Module<TModule> {
	public:
		explicit StaticModule(Args&&... args) {
			this->Instance = new TModule(std::forward<Args>(args));
		}
	};

	template<typename TModule>
	class ExternalModule final : public Module<TModule> {
	private:
		const std::string path;
		const std::string entryMethod;
		const std::string exitMethod;

		void* handle;

	public:
		ExternalModule(const std::string& path, const char* entryPoint, const char* exitPoint) : path(path), entryMethod(entryPoint), exitMethod(exitPoint) {
			handle = dlopen(path.c_str(), RTLD_NOW);
			if(handle == nullptr) {
				throw std::runtime_error(dlerror());
			}

			using EntryFunction = TModule* (*) ();
			auto entry = reinterpret_cast<EntryFunction>(dlsym(handle, entryMethod.c_str()));

			if(entry == nullptr) {
				// Function initialisation failed.
				throw std::runtime_error(dlerror());
			}

			this->Instance = entry();
		}

		~ExternalModule() override {
			using ExitFunction = void (*) (TModule*);
			auto exit = reinterpret_cast<ExitFunction>(dlsym(handle, exitMethod.c_str()));

			if(exit != nullptr) {
				exit(this->Instance);
			} else {
				std::cerr << dlerror() << std::endl;
			}

			if(dlclose(handle) != 0) {
				std::cerr << dlerror() << std::endl;
			}
		}
	};
}

#endif
