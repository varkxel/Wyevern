#include <Module.hpp>
#include <WyevernApplication.hpp>

#define ToString_Inner(str) #str
#define ToString(str) ToString_Inner(str)

using namespace Wyevern;

int main(int argc, char** argv) {
	Module<WyevernApplication> application(
		std::string(WyeLoader_GamePath),
		ToString(Wyevern_Application_Entry_Function_Name),
		ToString(Wyevern_Application_Exit_Function_Name)
	);
	std::shared_ptr<WyevernApplication> instance = application.Instance();

	return EXIT_SUCCESS;
}
