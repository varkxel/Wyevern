#include <WyeGen.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

const char* WyevernNamespace = "WyeMaths";
const char* WyevernComment = "// == WYEVERN GAME ENGINE == //\n";

size_t Swizzles_Count(size_t dimensions)
{
	size_t result = dimensions;
	for(size_t i = 1; i < dimensions; ++i)
	{
		result *= dimensions;
	}
	return result;
}

typedef struct
{
	char** swizzles;
	size_t swizzles_length;
	
	const char* components;
	size_t components_length;
}
SwizzleList;

SwizzleList Swizzles_Create(const char* components)
{
	SwizzleList created;
	created.components = components;
	created.components_length = strlen(components);
	return created;
}

uint64_t SwizzleGen_npot(uint64_t num)
{
	num--;
	num |= num >> 1ul;
	num |= num >> 2ul;
	num |= num >> 4ul;
	num |= num >> 8ul;
	num |= num >> 16ul;
	num |= num >> 32ul;
	num++;
	return num;
}

void Swizzles_Generate(SwizzleList* list)
{
	// Get the total amount of possible swizzles.
	list->swizzles_length = Swizzles_Count(list->components_length);
	
	// Allocate the array
	list->swizzles = malloc(sizeof(char*) * list->swizzles_length);
	
	for(size_t iSwizzle = 0; iSwizzle < list->swizzles_length; ++iSwizzle)
	{
		uint64_t componentIndices[list->components_length];
		for(unsigned i = 0; i < list->components_length; ++i)
		{
			const uint64_t components_npot = SwizzleGen_npot(list->components_length);
			uint64_t mask = (components_npot - 1) << (i * (components_npot / 2));
			
			uint64_t divisor = (uint64_t) pow((double) components_npot, i);
			
			// Clamp minimum to 1
			if(divisor <= 0) divisor = 1;
			
			componentIndices[i] = (((iSwizzle & mask) / divisor) + 1) % list->components_length;
		}
		
		list->swizzles[iSwizzle] = calloc(list->components_length + 1, sizeof(char));
		
		for(unsigned i = 0; i < list->components_length; ++i)
		{
			list->swizzles[iSwizzle][i] = list->components[componentIndices[i]];
		}
	}
}

void Permutations_Free(SwizzleList* list)
{
	for(size_t i = 0; i < list->swizzles_length; ++i)
	{
		free(list->swizzles[i]);
	}
	free(list->swizzles);
}

SwizzleList Permutations_TrimTo(const SwizzleList list, const unsigned characters)
{
	SwizzleList results;
	results.components = list.components;
	results.components_length = list.components_length;
	results.swizzles_length = list.swizzles_length;
	results.swizzles = malloc(sizeof(char*) * results.swizzles_length);
	
	for(unsigned i = 0; i < results.swizzles_length; ++i)
	{
		results.swizzles[i] = calloc(results.components_length + 1, sizeof(char));
		for(size_t character = 0; character < results.swizzles_length; ++character)
		{
			results.swizzles[i][character] = list.swizzles[i][character];
		}
	}
	return results;
}
/*
SwizzleList Permutations_StripComponents(const SwizzleList list, const char* componentsContain)
{
	SwizzleList results;
	
}*/

int main()
{
	SwizzleList xyzw = Swizzles_Create("wxyz");
	Swizzles_Generate(&xyzw);
	
	for(unsigned dimensions = 2; dimensions <= 4; ++dimensions)
	{
		char nameString[128];
		snprintf(nameString, 128, "Vector%d", dimensions);
		
		FILE* file = WyeGen_Header_Create(nameString, WyevernNamespace, WyevernComment);
		
		fprintf(file, "\n#define WYEMATHSINTERNAL_DEFINESWIZZLES_VECTOR%d(type_internal_) \\\n", dimensions);
		
		
		WyeGen_Header_End(file);
	}
	
	return EXIT_SUCCESS;
}
