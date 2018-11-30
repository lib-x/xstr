#include "src/str.h"
#include <stdio.h>

#define ER  error =

int main(void)
{
	xstr_t thing = NULL;
	x_error_t error;

	ER xstr_init(&thing, 0); /* Capacity will auto-change, but it's faster if you set it ahead of time */
	if (error != XE_NONE) return 1;

	ER xstr_cpy_c(thing, "hello");
	if (error != XE_NONE) return 1;

	puts(*thing);
	return 0;
}
