#include <Module.hpp>
#include <WyevernApplication.hpp>

#define ToString_Inner(str) #str
#define ToString(str) ToString_Inner(str)

int main(int argc, char** argv) {
	Wyevern::Module<Wyevern::WyevernApplication> application(
		std::string(WyeLoader_WEX_Path),
		ToString(Wyevern_Application_Entry_Function_Name),
		ToString(Wyevern_Application_Exit_Function_Name)
	);
	auto instance = application.Instance();

	return EXIT_SUCCESS;
}
