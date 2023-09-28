#include "WyeGen.h"

#include <ctype.h>

FILE* WyeGen_Header_Create(const char* name, const char* namespace, const char* comment)
{
	#define filename_bufferSize 1024
	char filename[filename_bufferSize];
	snprintf(filename, filename_bufferSize, "%s.gen.hpp", name);
	
	FILE* file = fopen(filename, "w");
	
	fprintf(file, "\n%s\n", comment);
	
	#define guardMacroSize 1024
	char guardMacro[guardMacroSize];
	snprintf(guardMacro, guardMacroSize, "%s_GENERATED_%s_INCLUDED", namespace, name);
	
	// Convert macro to uppercase
	for(size_t i = 0; i < guardMacroSize; ++i)
	{
		if(guardMacro[i] == '\0')
		{
			break;
		}
		
		guardMacro[i] = (char) toupper(guardMacro[i]);
	}
	
	fprintf(file, "\n#ifndef %s\n#define %s\n", guardMacro, guardMacro);
	
	return file;

	#undef filename_bufferSize
	#undef guardMacroSize
}

void WyeGen_Header_End(FILE* file)
{
	fprintf(file, "\n#endif\n");
	fclose(file);
}
