#include "include/str.h"
#include <stdio.h>

int main(void)
{
	xstr_t thing;

	thing = xstr_init(0); /* Capacity will auto-change, but it's faster if you set it ahead of time */
	if (thing == NULL) return 1;
	thing = xstr_set(thing, "uwu");
	thing = xstr_cat_c(thing, "uwu");

	puts(*thing);

	return 0;
}