#include "str.h"
#include <stdio.h>

int main(void)
{
	xstr_t thing = NULL;
	x_error_t error;

	error = xstr_init_set(&thing, "hello"); /* Capacity will auto-change, but it's faster if you set it ahead of time */
	if (error != XE_NONE)
		return 1;

	error = xstr_cat_c(thing, " world");
	if (error != XE_NONE)
		return 1;

	printf("Before substitution: %s\n", *thing);


	error = xstr_delete(thing, 0, 4);
	if (error != XE_NONE)
	{
		fprintf(stderr, "\n%d\n", error);
		return 1;
	}

	error = xstr_insert_c(thing, "Hi there,", 0);
	if (error != XE_NONE)
		return 1;

	printf("After substitution: %s\n", *thing);

	error = xstr_push(thing, '!');
	if (error != XE_NONE)
		return 1;

	printf("After push: %s\n", *thing);
	printf("Len: %lu\n", xstrlen(thing));

	return 0;
}
