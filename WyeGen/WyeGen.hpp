#ifndef WYEGEN_INCLUDED
#define WYEGEN_INCLUDED

#include <fstream>
#include <string>

namespace Wyevern
{
	class WyeGen
	{
	protected:
		std::ofstream file;

	public:
		explicit WyeGen(const std::string& path);
		~WyeGen();

		void Comment(std::string comment);
		void Comment_Multiline(std::string comment);

		void Space(int lines = 1);

		void Macro_Define(const std::string& name, std::string value = "");
		void Macro_IfDefined(const std::string& macro);
		void Macro_IfDefined_Not(const std::string& macro);
		void Macro_IfDefined_End();

		void Raw(const std::string& line);
	};
}

#endif