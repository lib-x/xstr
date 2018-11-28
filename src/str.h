#ifndef _XSTR_H
#define _XSTR_H

#include <stdint.h>

/* Types and stuff */
typedef struct
{
	char * val;
	uint16_t cap;
	uint16_t len;
} * _xstr_t;

char typedef ** xstr_t;

typedef enum
{
	XE_NONE = 0,
	XE_ALLOC,
	XE_DUP,
	XE_NORANGE,
	XE_OTHER
} x_error_t;

/* Macros */
#define xstrlen(x)   (((_xstr_t) x)->len)

/* Functions and stuff */
x_error_t xstr_init(xstr_t * dest, uint16_t size);

x_error_t xstr_init_set(xstr_t dest, char * src);

x_error_t xstr_cpy(xstr_t dest, xstr_t src);

x_error_t xstr_cpy_c(xstr_t dest, char * src);

x_error_t xstr_cat(xstr_t dest, xstr_t src);

x_error_t xstr_cat_c(xstr_t dest, char * src);

x_error_t xstr_insert(xstr_t dest, xstr_t src, uint16_t index);

x_error_t xstr_insert_c(xstr_t dest, char * src, uint16_t index);

x_error_t xstr_delete(xstr_t dest, uint16_t start, uint16_t end);

x_error_t xstr_push(xstr_t dest, char ch);

x_error_t xstr_free(xstr_t src);

#endif
