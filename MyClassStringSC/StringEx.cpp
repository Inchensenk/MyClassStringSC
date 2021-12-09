#include "StringEx.h"

int strLength(char* str) 
{
	int counter = 0;
	
	while (str[counter]!='\0')
	{
		counter++;
	}
	return counter;

}