#ifndef STRING_C
#define STRING_C

#include <toast.h>

uint64_t strlen(char *string)
{
	uint64_t l = 0;
	while (string[l] != 0)
		l++;
	return l;
}

#endif
