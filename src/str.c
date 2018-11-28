#include "str.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#define X_CHECK_ALLOC(dest)    if ((dest).val == NULL) {return XE_ALLOC;}

x_error_t xstr_init(xstr_t * dest, size_t size)
{
	_xstr_t str;

	if (size == SIZE_MAX) return XE_OVERFLOW;

	str = malloc(sizeof (_xstr_t));

	if (size == 0) size = 63;

	str->val = malloc(size + 1); /* String size + '\0' */

	X_CHECK_ALLOC(*str);

	str->cap = size;
	str->len = 0;

	*dest = (xstr_t) str;

	return XE_NONE;
}

x_error_t xstr_init_set(xstr_t dest, char * src)
{
	_xstr_t str;

	str = NULL;

	xstr_init((xstr_t *) &str, strlen(src));

	if (str->val != NULL)
	{
		strcpy(str->val, src);
	}

	dest = (xstr_t) str;

	return XE_NONE;
}

x_error_t xstr_cpy(xstr_t dest, xstr_t src)
{
	_xstr_t _dest;
	_xstr_t _src;
	size_t cap;

	_dest = (_xstr_t) dest;
	_src  = (_xstr_t) src;

	if (_dest->cap < _src->len)
	{
		if (_src->len < (SIZE_MAX / 2))
			cap = _src->len * 2;
		else /* Overflow */
			cap = _src->len;
		/**/

		_dest->val = realloc(_dest->val, cap);
		X_CHECK_ALLOC(*_dest);
		_dest->cap = cap;
	}

	strcpy(_dest->val, _src->val);
	_dest->len = _src->len;

	return XE_NONE;
}

x_error_t xstr_cpy_c(xstr_t dest, char * src)
{
	size_t ssize;
	size_t cap;
	_xstr_t _dest;

	_dest = (_xstr_t) dest;
	ssize = strlen(src);

	if (_dest->cap < ssize)
	{
		if (ssize < (SIZE_MAX) / 2)
			cap = ssize * 2;
		else /* Overflow */
			cap = ssize;
		/**/

		_dest->val = realloc(_dest->val, ssize * 2);
		X_CHECK_ALLOC(*_dest);
		_dest->cap = ssize * 2;
	}

	strcpy(_dest->val, src);
	_dest->len = ssize;

	return XE_NONE;
}

x_error_t xstr_cat(xstr_t dest, xstr_t src)
{
	_xstr_t _dest;
	_xstr_t _src;
	size_t cap;

	_dest = (_xstr_t) dest;
	_src  = (_xstr_t) src;

	if (_dest->len > SIZE_MAX - _src->len) return XE_OVERFLOW;

	if (_dest->cap < _src->len + _dest->len) /* No need for addition end-of-string nil byte */
	{
		if (_dest->len + _src->len < (size_t) (SIZE_MAX / 1.5))
			cap = _src->len + _dest->len;
		else /* Overflow */
			cap = (size_t) (1.5 * (_src->len + _dest->len));
		/**/

		_dest->val = realloc(_dest->val, cap);
		X_CHECK_ALLOC(*_dest);

		_dest->cap = cap;
	}

	strcat(_dest->val, _src->val);
	_dest->len = _dest->len + _src->len;

	return XE_NONE;
}

x_error_t xstr_cat_c(xstr_t dest, char * src)
{
	size_t slen;
	size_t cap;
	_xstr_t _dest;

	_dest = (_xstr_t) dest;
	slen = strlen(src);

	if (_dest->len > SIZE_MAX - slen) return XE_OVERFLOW;

	if (_dest->cap < slen + _dest->len)
	{
		if (_dest->len + slen < (size_t) (SIZE_MAX / 1.5))
			cap = slen + _dest->len;
		else /* Overflow */
			cap = (size_t) (1.5 * (slen + _dest->len));
		/**/

		_dest->val = realloc(_dest->val, cap);
		X_CHECK_ALLOC(*_dest);

		_dest->cap = cap;
	}

	strcat(_dest->val, src);
	_dest->len = slen + _dest->len;

	return XE_NONE;
}

x_error_t xstr_insert(xstr_t dest, xstr_t src, size_t index)
{
	char * tmp;
	x_error_t err;

	tmp = strdup(*dest);
	if (tmp == NULL) return XE_DUP;
	tmp[index] = 0;

	err = xstr_cpy_c(dest, tmp);
	if (err != XE_NONE) return err;
	err = xstr_cat(dest, src);
	if (err != XE_NONE) return err;
	err = xstr_cat_c(dest, tmp + index + 1);

	free(tmp);

	return err;
}

x_error_t xstr_insert_c(xstr_t dest, char * src, size_t index)
{
	char * tmp;
	x_error_t err;

	tmp = strdup(*dest);
	if (tmp == NULL) return XE_DUP;

	tmp[index] = 0;

	err = xstr_cpy_c(dest, tmp);
	if (err != XE_NONE) return err;
	err = xstr_cat_c(dest, src);
	if (err != XE_NONE) return err;
	err = xstr_cat_c(dest, tmp + index + 1);

	free(tmp);

	return err;
}

x_error_t xstr_delete(xstr_t dest, size_t start, size_t end)
{
	char * tmp1;
	char * tmp2;
	x_error_t err;

	if (start == end) return XE_NORANGE;

	(*dest)[start] = 0;

	tmp1 = strdup(*dest);
	if (tmp1 == NULL) return XE_DUP;

	tmp2 = strdup(*(dest) + end);
	if (tmp2 == NULL) { free(tmp1); return XE_DUP; }

	err = xstr_cpy_c(dest, tmp1);
	if (err != XE_NONE) { free(tmp1); free(tmp2); return err; }

	xstr_cat_c(dest, tmp2);

	free(tmp1);
	free(tmp2);

	return err;
}

x_error_t xstr_push(xstr_t dest, char ch)
{
	char * tmp;
	_xstr_t _dest;

	_dest = (_xstr_t) dest;

	if (_dest->len == SIZE_MAX) return XE_OVERFLOW;

	if (_dest->cap > _dest->len + 1)
	{
		_dest->len++;
		_dest->val[_dest->len - 1] = ch;
		_dest->val[_dest->len] = 0;
		return XE_NONE;
	}

	if (_dest->cap < SIZE_MAX / 2)
		tmp = realloc(_dest->val, _dest->cap * 2);
	else
		tmp = realloc(_dest->val, _dest->cap);
	/**/

	if (tmp == NULL)
	{

		free(_dest->val);
		free(_dest);
		return XE_ALLOC;
	}

	_dest->val = tmp;

	_dest->cap *= 2;
	_dest->len++;

	_dest->val[_dest->len - 1] = ch;

	return XE_NONE;
}

x_error_t xstr_free(xstr_t src)
{
	_xstr_t _src;

	_src = (_xstr_t) src;

	free(_src->val);
	free(_src);

	return XE_NONE;
}
