#include "str.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

#define X_CHECK_ALLOC(x)    do { if (x == NULL) {return XE_ALLOC;} } while (0)

x_error_t xstr_init(xstr_t * dest, size_t size)
{
	struct _xstr_s * str;

	if (size == SIZE_MAX)
	{
		return XE_OVERFLOW;
	}

	str = malloc(sizeof (*str));
	X_CHECK_ALLOC(str);

	if (size == 0)
	{
		size = (size_t) 63;
	}

	str->val = malloc(size + 1); /* String size + '\0' */
	if (str->val == NULL)
	{
		free(str);
		return XE_ALLOC;
	}

	str->cap = size;
	str->len = 0;

	*dest = (xstr_t) str;
	return XE_NONE;
}

x_error_t xstr_init_set_n(xstr_t * dest, char * src, size_t src_len)
{
	struct _xstr_s * str;

	str = NULL;

	xstr_init((xstr_t *) &str, src_len);

	if (str->val != NULL)
	{
		strcpy(str->val, src);
	}

	*dest = (xstr_t) str;

	return XE_NONE;
}

x_error_t xstr_cpy(xstr_t dest, xstr_t src)
{
	struct _xstr_s * _dest;
	struct _xstr_s * _src;

	_dest = (struct _xstr_s *) dest;
	_src  = (struct _xstr_s *) src;

	if (_src == NULL || _dest == NULL)
		return XE_ISNULL;
	if (_src->len == SIZE_MAX)
		return XE_OVERFLOW;

	if (_dest->cap < _src->len)
	{
		if (_src->len < SIZE_MAX / 2)
		{
			_dest->cap = (size_t) (_src->len * 2 - 1);
		}
		else
		{
			_dest->cap = _src->len;
		}

		_dest->val = realloc(_dest->val, _dest->cap + 1);
		X_CHECK_ALLOC(_dest->val);
	}

	strcpy(_dest->val, _src->val);
	_dest->len = _src->len;

	return XE_NONE;
}

x_error_t xstr_cpy_c_n(xstr_t dest, char * src, size_t ssize)
{
	struct _xstr_s * _dest;

	_dest = (struct _xstr_s *) dest;

	if (dest == NULL)
		return XE_ISNULL;
	if (ssize == SIZE_MAX)
		return XE_OVERFLOW;

	if (_dest->cap < ssize)
	{
		if (ssize < SIZE_MAX / 2)
		{
			_dest->cap = (size_t) (ssize * 2 - 1);
		}
		else if (ssize != SIZE_MAX)
		{
			_dest->cap = ssize;
		}

		_dest->val = realloc(_dest->val, _dest->cap + 1);
		X_CHECK_ALLOC(_dest->val);
	}

	strcpy(_dest->val, src);

	_dest->len = ssize;
	_dest->cap = ssize;

	return XE_NONE;
}

x_error_t xstr_cat(xstr_t dest, xstr_t src)
{
	struct _xstr_s * _dest;
	struct _xstr_s * _src;

	_dest = (struct _xstr_s *) dest;
	_src  = (struct _xstr_s *) src;

	if (_dest->len > SIZE_MAX - _src->len)
		return XE_OVERFLOW;

	if (_dest->cap < _src->len + _dest->len) /* No need for addition end-of-string nil byte */
	{
		if (_dest->len + _src->len < (SIZE_MAX / 2))
		{
			_dest->cap = (size_t) ((_src->len + _dest->len) * 2 - 1);
		}
		else
		{
			_dest->cap = (size_t) _src->len + _dest->len;
		}

		_dest->val = realloc(_dest->val, _dest->cap + 1);
		X_CHECK_ALLOC(_dest->val);
	}

	strcat(_dest->val, _src->val);
	_dest->len = _dest->len + _src->len;

	return XE_NONE;
}

x_error_t xstr_cat_c_n(xstr_t dest, char * src, size_t src_len)
{
	struct _xstr_s * _dest;

	_dest = (struct _xstr_s *) dest;


	if (_dest->len > SIZE_MAX - src_len)
		return XE_OVERFLOW;

	if (_dest->cap < src_len + _dest->len)
	{
		if (_dest->len + src_len < SIZE_MAX / 2)
		{
			_dest->cap = (size_t) ((src_len + _dest->len) * 2 - 1);
		}
		else 
		{
			_dest->cap = (size_t) src_len + _dest->len;
		}

		_dest->val = realloc(_dest->val, _dest->cap + 1);
		X_CHECK_ALLOC(_dest->val);
	}

	strcat(_dest->val, src);
	_dest->len = src_len + _dest->len;

	return XE_NONE;
}

x_error_t xstr_insert(xstr_t dest, xstr_t src, size_t index)
{
	char * tmp;
	char * tmp1;
	x_error_t err;

	if (src == NULL)
	{
		return XE_ISNULL;
	}

	tmp = strdup(*dest);
	if (tmp == NULL)
	{
		return XE_DUP;
	}

	tmp1 = strdup(tmp + index);
	if (tmp == NULL)
	{
		return XE_DUP;
	}

	tmp[index] = 0;

	err = xstr_cpy_c(dest, tmp);
	if (err != XE_NONE)
	{
		return err;
	}

	err = xstr_cat_c_n(dest, *src, ((struct _xstr_s *) src)->len);
	if (err != XE_NONE)
	{
		return err;
	}
	err = xstr_cat_c(dest, tmp1);

	free(tmp);
	free(tmp1);

	return err;
}

x_error_t xstr_insert_c_n(xstr_t dest, char * src, size_t index, size_t src_len)
{
	char * tmp;
	char * tmp1;
	x_error_t err;

	tmp = strdup(*dest);
	if (tmp == NULL)
	{
		return XE_DUP;
	}

	tmp1 = strdup(tmp + index);
	if (tmp == NULL)
	{
		return XE_DUP;
	}

	tmp[index] = 0;

	err = xstr_cpy_c(dest, tmp);
	if (err != XE_NONE)
	{
		return err;
	}

	err = xstr_cat_c_n(dest, src, src_len);
	if (err != XE_NONE)
	{
		return err;
	}
	err = xstr_cat_c(dest, tmp1);

	free(tmp);
	free(tmp1);

	return err;
}

x_error_t xstr_delete(xstr_t dest, size_t start, size_t end)
{
	char * tmp1;
	char * tmp2;
	x_error_t err;

	if (start == end || end < start)
	{
		return XE_NORANGE;
	}

	(*dest)[start] = 0;

	tmp1 = strdup(*dest);
	if (tmp1 == NULL)
	{
		return XE_DUP;
	}

	tmp2 = strdup(*(dest) + end + 1);
	if (tmp2 == NULL)
	{
		free(tmp1); 
		return XE_DUP;
	}

	err = xstr_cpy_c(dest, tmp1);
	if (err != XE_NONE)
	{
		free(tmp1);
		free(tmp2);
		return err;
	}

	err = xstr_cat_c(dest, tmp2);

	free(tmp1);
	free(tmp2);

	return err;
}

x_error_t xstr_push(xstr_t dest, char ch)
{
	char * tmp;
	struct _xstr_s * _dest;

	_dest = (struct _xstr_s *) dest;

	if (_dest->len == SIZE_MAX)
	{
		return XE_OVERFLOW;
	}

	if (_dest->cap > _dest->len + 1)
	{
		_dest->len++;
		_dest->val[_dest->len - 1] = ch;
		_dest->val[_dest->len] = 0;
		return XE_NONE;
	}

	if (_dest->cap < SIZE_MAX / 2)
	{
		tmp = realloc(_dest->val, _dest->cap * 2);
		_dest->cap = _dest->cap * 2 - 1;
	}
	else if (_dest->cap < SIZE_MAX - 1)
	{
		tmp = realloc(_dest->val, _dest->cap + 2);
		_dest->cap++;
	}
	else return XE_OVERFLOW;

	if (tmp == NULL)
	{

		free(_dest->val);
		free(_dest);
		return XE_ALLOC;
	}

	_dest->val = tmp;

	_dest->len++;
	_dest->val[_dest->len - 1] = ch;
	_dest->val[_dest->len] = 0;

	return XE_NONE;
}

x_error_t xstr_free(xstr_t src)
{
	struct _xstr_s * _src;

	_src = (struct _xstr_s *) src;

	free(_src->val);
	free(_src);

	return XE_NONE;
}
