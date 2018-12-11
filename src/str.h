#ifndef _XSTR_H
#define _XSTR_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "config.h"

/* Types and stuff */
struct _xstr_s
{
	char * val;
	size_t cap;
	size_t len;
};

typedef char ** xstr_t;

typedef enum
{
	XE_NONE = 0,
	XE_ALLOC,
	XE_DUP,
	XE_NORANGE,
	XE_OVERFLOW,
	XE_ISNULL
} x_error_t;


/* Functions and stuff */
x_error_t xstr_init(xstr_t * dest, size_t size);

x_error_t xstr_init_set_n(xstr_t * dest, char * src, size_t src_len);

x_error_t xstr_cpy(xstr_t dest, xstr_t src);

x_error_t xstr_cpy_c_n(xstr_t dest, char * src, size_t src_len);

x_error_t xstr_cat(xstr_t dest, xstr_t src);

x_error_t xstr_cat_c_n(xstr_t dest, char * src, size_t src_len);

x_error_t xstr_insert_c_n(xstr_t dest, char * src, size_t index, size_t src_len);

x_error_t xstr_insert(xstr_t dest, xstr_t src, size_t index);

x_error_t xstr_delete(xstr_t dest, size_t start, size_t end);

x_error_t xstr_push(xstr_t dest, char ch);

x_error_t xstr_free(xstr_t src);

/* Macros */
#define xstrlen(x)   (((struct _xstr_s *) x)->len)

#define xstr_init_set(dest, src)         xstr_init_set_n((dest), (src), strlen(src))
#define xstr_cpy_c(dest, src)            xstr_cpy_c_n((dest), (src), strlen(src))
#define xstr_cat_c(dest, src)            xstr_cat_c_n((dest), (src), strlen(src))
#define xstr_insert_c(dest, src, index)  xstr_insert_c_n((dest), (src), index, strlen(src))

#endif
