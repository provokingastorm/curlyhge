#include "curlycore.h"
#include <string>
#include <cctype>


char* ChzStrDuplicate(const char* SrcString)
{
	char* DuplicatedString = NULL;

	if(SrcString != NULL)
	{
		const int Size = strlen(SrcString);

		if(Size > 0)
		{
			DuplicatedString = new char[Size];
			strncpy(DuplicatedString, SrcString, Size);
		}
	}

	return DuplicatedString;
}

char* ChzStrLower(const char* SrcString)
{
	char* LowerString = NULL;

	if(SrcString != NULL)
	{
		int Size = strlen(SrcString);

		if(Size > 0)
		{
			// Add 1 for the null-terminating character, which strlen doesn't include.
			Size += 1;

			LowerString = new char[Size];
			strcpy(LowerString, SrcString);
			int i = 0;

			while(LowerString[i] != '\0' && i < Size)
			{
				LowerString[i] = tolower(LowerString[i]);
				i++;
			}
		}
	}

	return LowerString;
}

int MaxInt(int First, int Second)
{
	return (First > Second) ? First : Second;
}

float MaxFloat(float First, float Second)
{
	return (First > Second) ? First : Second;
}

int MinInt(int First, int Second)
{
	return (First < Second) ? First : Second;
}

float MinFloat(float First, float Second)
{
	return (First < Second) ? First : Second;
}

// EOF
