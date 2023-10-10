#include "WyeGen.hpp"

#include <cstdint>

using namespace Wyevern;

WyeGen::WyeGen(const std::string& path)
{
	file.open(path);
}

WyeGen::~WyeGen()
{
	file.close();
}

void InsertOnCharacter(std::string& comment, const char character, const std::string& string, long long int offset = 1)
{
	for (std::size_t i = 0; i < comment.length(); ++i)
	{
		if (comment[i] == character)
		{
			comment.insert(i += offset, string);
			i += string.size();
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

void WyeGen::Space(int lines)
{
	for(int i = 0; i < lines - 1; ++i)
	{
		file << "\n";
	}
	file << std::endl;
}

void WyeGen::Macro_Define(const std::string& name, std::string value)
{
	file << "#define " << name;
	if(!value.empty())
	{
		InsertOnCharacter(value, '\n', "\t\\", 0);
		InsertOnCharacter(value, '\n', "\t", 1);
		file << " " << value;
	}
	file << std::endl;
}

void WyeGen::Macro_IfDefined(const std::string& macro)
{
	file << "#ifdef ";
	file << macro << std::endl;
}

void WyeGen::Macro_IfDefined_Not(const std::string& macro)
{
	file << "#ifndef ";
	file << macro << std::endl;
}

void WyeGen::Macro_IfDefined_End()
{
	file << "#endif" << std::endl;
}

void WyeGen::Raw(const std::string& line)
{
	file << line << std::endl;
}
