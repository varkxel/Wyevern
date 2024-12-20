#include <Module.hpp>
#include <WyevernApplication.hpp>

#include <memory>

// EXIT_SUCCESS / EXIT_FAILURE
#include <cstdlib>

#define ToString_Inner(str) #str
#define ToString(str) ToString_Inner(str)

using namespace Wyevern;

int main(int argc, char** argv) {
	std::unique_ptr<Module<WyevernApplication>> application = nullptr;
	std::shared_ptr<WyevernApplication> instance = nullptr;
	try {
		application = std::make_unique<Module<WyevernApplication>>(
			std::string(WyeLoader_GamePath),
			ToString(Wyevern_Application_Entry_Function_Name),
			ToString(Wyevern_Application_Exit_Function_Name)
		);
		instance = application->Instance();
	} catch(const std::runtime_error& error) {
		std::cerr << "WyeLoader failed to start.\nError: " << error.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#undef ToString_Inner
#undef ToString
