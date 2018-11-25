#include <stdio.h>
#include "../include/str.h"

#define X_CHECK_ALLOC(dest)    if ((dest).val == NULL) {return XE_ALLOC;}

x_error_t xstr_init(xstr_t * dest, uint16_t size)
{
	_xstr_t str;

	str = malloc(sizeof (_xstr_t));

	if (size == 0) size = 63;

	str->val = malloc(size + 1); // String size + '\0'

	X_CHECK_ALLOC(*str);

	str->cap = size;
	str->len = 0;

	*dest = (xstr_t) str;

	return XE_NONE;
}

x_error_t xstr_set(xstr_t dest, const char * src)
{
	uint16_t ssize;
	_xstr_t _dest;

	_dest = (_xstr_t) dest;
	ssize = strlen(src);

	if (_dest->cap < ssize)
	{
		_dest->val = realloc(_dest->val, ssize + 1);
		X_CHECK_ALLOC(*_dest);
	}

	strcpy(_dest->val, src);
	_dest->len = ssize;

	return XE_NONE;
}

x_error_t xstr_cpy(xstr_t dest, xstr_t src)
{
	_xstr_t _dest;
	_xstr_t _src;

	_dest = (_xstr_t) dest;
	_src  = (_xstr_t) src;

	if (_dest->cap < _src->len)
	{
		_dest->val = realloc(_dest->val, _src->len + 1);
		X_CHECK_ALLOC(*_dest);
	}

	strcpy(_dest->val, _src->val);
	_dest->len = _src->len;

	return XE_NONE;
}

x_error_t xstr_cat(xstr_t dest, xstr_t src)
{
	_xstr_t _dest;
	_xstr_t _src;

	_dest = (_xstr_t) dest;
	_src  = (_xstr_t) src;

	if (_dest->cap < _src->len + _dest->len) /* No need for addition end-of-string nil byte */
	{
		_dest->val = realloc(_dest->val, _src->len + _dest->len + 1);
		X_CHECK_ALLOC(*_dest);

		_dest->cap = _src->len + _dest->len;
	}

	strcat(_dest->val, _src->val);
	_dest->len = _dest->len + _src->len;

	return XE_NONE;
}

x_error_t xstr_cat_c(xstr_t dest, const char * src)
{
	uint16_t slen;
	_xstr_t _dest;

	_dest = (_xstr_t) dest;
	slen = strlen(src);

	if (_dest->cap < slen + _dest->len)
	{
		_dest->val = realloc(_dest->val, slen + _dest->cap + 1);
		X_CHECK_ALLOC(*_dest);

		_dest->cap = slen + _dest->cap;
	}

	strcat(_dest->val, src);
	_dest->len = slen + _dest->len;

	return XE_NONE;
}