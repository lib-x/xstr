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

	ER xstr_cat_c(thing, " world");
	if (error != XE_NONE) return 1;

	printf("Before substitution: %s\n", *thing);

	ER xstr_delete(thing, 0, 4);
	if (error != XE_NONE) return 1;

	ER xstr_insert_c(thing, "Hi there,", 0);
	if (error != XE_NONE) return 1;

	printf("After substitution: %s\n", *thing);

	ER xstr_push(thing, '!');
	if (error != XE_NONE) return 1;

	printf("After push: %s\n", *thing);
	return 0;
}