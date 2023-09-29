#include "WyeGen.hpp"

#include <cstdint>

using namespace Wyevern;

WyeGen::WyeGen(const char* path)
{
	file.open(path);
}

WyeGen::~WyeGen()
{
	file.close();
}

void InsertOnCharacter(std::string& comment, const char character, const char* string)
{
	for (std::size_t i = 0; i < comment.length(); ++i)
	{
		if (comment[i] == character)
		{
			comment.insert(i + 1, string);
		}
	}
}

void WyeGen::Comment(std::string comment)
{
	const auto prefix = "// ";
	comment.insert(0, prefix);

	InsertOnCharacter(comment, '\n', prefix);

	file << comment << std::endl;
}

void WyeGen::Comment_Multiline(std::string comment)
{
	comment.insert(0, "/*\n");
	InsertOnCharacter(comment, '\n', "\t");
	comment.insert(comment.length(), "\n*/");

	file << comment << std::endl;
}
