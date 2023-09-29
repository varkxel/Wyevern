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
		explicit WyeGen(const char* path);
		~WyeGen();

		void Comment(std::string comment);
		void Comment_Multiline(std::string comment);
	};
}

#endif