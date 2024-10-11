#ifndef WYEVERN_MODULE_INCLUDED
#define WYEVERN_MODULE_INCLUDED

#include <string>
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace Wyevern {
	template<typename TModule, const char* entryPoint, const char* exitPoint>
	class Module {
	protected:
		const std::string path;
		void* handle;
		
	public:
		explicit Module(const std::string& path) : path(path) {
			handle = dlopen(path.c_str(), RTLD_NOW);
			if(handle == nullptr) {
				throw std::runtime_error(dlerror());
			}
		}
		
		~Module() {
			int status = dlclose(handle);
			if(status != 0) {
				std::cerr << dlerror() << std::endl;
			}
		}
		
		std::shared_ptr<TModule> Instance() {
			using EntryFunction = TModule* (*) ();
			using ExitFunction = void (*) (TModule*);
			
			auto entry = reinterpret_cast<EntryFunction>(dlsym(handle, entryPoint));
			auto exit = reinterpret_cast<ExitFunction>(dlsym(handle, exitPoint));
			
			if(entry == nullptr || exit == nullptr) {
				// Function initialisation failed.
				throw std::runtime_error(dlerror());
			}
			
			return std::shared_ptr<TModule>(entry(), [exit](TModule* module){ exit(module); });
		}
	};
}

#endif
