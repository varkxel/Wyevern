#ifndef WYEGEN_INCLUDED
#define WYEGEN_INCLUDED

#include <stdio.h>

FILE* WyeGen_Header_Create(const char* name, const char* namespace, const char* comment);

void WyeGen_Header_End(FILE* file);

#endif