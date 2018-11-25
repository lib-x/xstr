#include "include/str.h"
#include <stdio.h>

int main(void)
{
	xstr_t thing = NULL;
	x_error_t error;

	error = xstr_init(&thing, 0); /* Capacity will auto-change, but it's faster if you set it ahead of time */
	if (error != XE_NONE) return 1;
	error = xstr_set(thing, "uwu");
	if (error != XE_NONE) return 1;
	error = xstr_cat_c(thing, "uwu");
	if (error != XE_NONE) return 1;

	puts(*thing);

	return 0;
}