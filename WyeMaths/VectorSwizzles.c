#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

size_t Permutations(char*** results)
{
	const char* baseString = "wwww";
	const unsigned permutations = 4 * 4 * 4 * 4;
	
	*results = malloc(sizeof(char*) * permutations);
	
	for(unsigned n = 0; n < permutations; ++n)
	{
		unsigned increments[4];
		for(int i = 0; i < 4; ++i)
		{
			unsigned thisMask = 0b00000011 << (i * 2);
			
			int divisor = (int) powl(4, i);
			if(divisor <= 0) divisor = 1;
			increments[i] = (((n & thisMask) / divisor) + 1) % 4;
		}
		
		(*results)[n] = malloc(sizeof(char) * 5);
		strcpy((*results)[n], baseString);
		
		for(int i = 0; i < 4; ++i)
		{
			(*results)[n][i] += (char) increments[i];
		}
	}
	
	return permutations;
}

void FreePermutations(char** resultsArray, size_t resultsLength)
{
	for(size_t i = 0; i < resultsLength; ++i)
	{
		free(resultsArray[i]);
	}
	free(resultsArray);
}

size_t TrimTo(char** permList, char*** results, unsigned dimensions)
{
	const unsigned perms = (unsigned) powl(4, dimensions);
	*results = malloc(sizeof(char*) * perms);
	
	for(unsigned i = 0; i < perms; ++i)
	{
		(*results)[i] = calloc(dimensions + 1, sizeof(char*));
		for(unsigned character = 0; character < dimensions; ++character)
		{
			(*results)[i][character] = permList[i][character];
		}
	}
	
	return perms;
}

size_t StripTo(char** permList, size_t permListLength, unsigned dimensions, char*** results)
{
	size_t count = 0;
	*results = malloc(sizeof(char*) * permListLength);
	
	for(size_t permIndex = 0; permIndex < permListLength; ++permIndex)
	{
		bool shouldStrip = false;
		for(unsigned i = 0; i < 4; ++i)
		{
			char offset = permList[permIndex][i];
			offset -= 'w';
			offset += 3;
			offset %= 4;
			
			shouldStrip |= offset >= dimensions;
		}
		
		if(!shouldStrip)
		{
			(*results)[count] = calloc(5, sizeof(char));
			strcpy((*results)[count], permList[permIndex]);
			++count;
		}
	}
	
	return count;
}

void GenerateHeaderGuard(FILE* file, unsigned dimension)
{
	const char* comment =
		"// == WYEVERN GAME ENGINE == //\n"
		"// This file is auto-generated and internal to the engine.\n"
		"// Please do not modify or include this file, instead edit VectorSwizzles.c or use Vector.hpp.\n";
	
	const size_t bufferSize = 256;
	char guardMacro[bufferSize];
	snprintf(guardMacro, bufferSize, "WYEMATHS_GENERATED_VECTOR%d_INCLUDED", dimension);
	
	fprintf(file, "%s\n#ifndef %s\n#define %s\n\n", comment, guardMacro, guardMacro);
}

void EndHeaderGuard(FILE* file)
{
	fprintf(file, "#endif\n");
}

void GenerateSwizzles(FILE* file, const unsigned vectorDimension)
{
	const size_t macroBuffer = 1024;
	char macroName[macroBuffer];
	snprintf(macroName, macroBuffer, "WYEMATHSINTERNAL_DEFINESWIZZLES_VECTOR%d", vectorDimension);
	
	const char* macroTypeParam = "type_internal_";
	
	fprintf(file, "#define %s(%s) ", macroName, macroTypeParam);
	
	char** results;
	size_t results_length = Permutations(&results);
	
	for(unsigned dim = 2; dim <= vectorDimension; ++dim)
	{
		char** dimensionSwizzles;
		size_t dimensionSwizzles_length = TrimTo(results, &dimensionSwizzles, dim);
		
		char** stripped;
		size_t stripped_length = StripTo(dimensionSwizzles, dimensionSwizzles_length, vectorDimension, &stripped);
		
		const size_t vectorBuffer = 1024;
		char vectorType[vectorBuffer];
		snprintf(vectorType, vectorBuffer, "Vector<%s, %d>", macroTypeParam, dim);
		
		for(int i = 0; i < stripped_length; ++i)
		{
			fprintf(file, " \\\n\tinline %s %s() const { return %s { ", vectorType, stripped[i], vectorType);
			
			char swizzleChar;
			for(size_t pos = 0; pos < 4; ++pos)
			{
				swizzleChar = stripped[i][pos];
				if(swizzleChar == '\0')
				{
					break;
				}
				
				fprintf(file, "%c, ", swizzleChar);
			}
			
			fprintf(file, "}; }");
		}
		
		FreePermutations(stripped, stripped_length);
		FreePermutations(dimensionSwizzles, dimensionSwizzles_length);
	}
	fprintf(file, "\n\n");
}

int main(int argc, char** argv)
{
	for(unsigned dimensions = 2; dimensions <= 4; ++dimensions)
	{
		const size_t bufferSize = 1024;
		char dest[bufferSize];
		snprintf(dest, bufferSize, "./Vector%d.gen.hpp", dimensions);
		
		FILE* destFile = fopen(dest, "w");
			GenerateHeaderGuard(destFile, dimensions);
			
			GenerateSwizzles(destFile, dimensions);
			
			EndHeaderGuard(destFile);
		fclose(destFile);
	}
}
