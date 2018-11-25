#ifndef _XSTR_H
#define _XSTR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

/* Types and stuff */
struct
{
	char * val;
	uint16_t cap;
	uint16_t len;
} typedef * _xstr_t;

char typedef ** xstr_t;

enum
{
	XE_ALLOC = INT_MIN,
	XE_OTHER
} x_error;

/* Functions and stuff */
xstr_t xstr_init(uint16_t size);

xstr_t xstr_set(xstr_t dest, const char * src);

xstr_t xstr_cpy(xstr_t dest, xstr_t src);

xstr_t xstr_cat(xstr_t dest, xstr_t src);

xstr_t xstr_cat_c(xstr_t dest, const char * src);

inline xstr_t str_init_set(const char * src);

inline xstr_t xstr_free(xstr_t src);

/* Inline functions */
inline xstr_t str_init_set(const char * src)
{
	_xstr_t str;

	str = (_xstr_t) (xstr_init(strlen(src)));

	if (str->val != NULL)
	{
		strcpy(str->val, src);
	}

	return (xstr_t) str;
}

inline xstr_t xstr_free(xstr_t src)
{
	_xstr_t _src;

	_src = (_xstr_t) src;

	free(_src->val);
	_src->cap = 0;
	_src->val = NULL;

	return (xstr_t) _src;
}

#endif