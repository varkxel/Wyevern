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

		virtual std::unique_ptr<TModule> Instance() = 0;
	};

	template<typename TModule>
	class StaticModule final : public Module<TModule> {
	public:
		std::unique_ptr<TModule> Instance() override {
			return std::make_unique<TModule>();
		}
	};

	template<typename TModule>
	class ExternalModule final : public Module<TModule> {
	protected:
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
		}
		
		~ExternalModule() override {
			if(dlclose(handle) != 0) {
				std::cerr << dlerror() << std::endl;
			}
		}
		
		std::shared_ptr<TModule> Instance() override {
			using EntryFunction = TModule* (*) ();
			using ExitFunction = void (*) (TModule*);
			
			auto entry = reinterpret_cast<EntryFunction>(dlsym(handle, entryMethod.c_str()));
			auto exit = reinterpret_cast<ExitFunction>(dlsym(handle, exitMethod.c_str()));
			
			if(entry == nullptr || exit == nullptr) {
				// Function initialisation failed.
				throw std::runtime_error(dlerror());
			}
			
			return std::shared_ptr<TModule>(entry(), [exit](TModule* module){ exit(module); });
		}
	};
}

#endif
