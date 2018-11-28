# xstr: A simpler string library

## Why to use this over other string libraries

- It's public domain
- You can access the internal string using `*str` instead of having to do `get_val(str)` or `str.val`
- Works with C90/C89, not just C99

## Why not to use this library

- You don't have libc available
- You're using a custom allocator
- You're have no allocator
- You need really high performance
- You're a programming-masochist
- You're using Python

## Example:

```
#include "include/str.h"
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

	ER xstr_push(thing, 'h');
	printf("After push: %s\n", *thing);

	return 0;
}
```

## API:

### Types:

#### x_error_t
```
typedef enum
{
	XE_NONE,
	XE_ALLOC,
	XE_DUP,
	XE_NORANGE,
	XE_OTHER
} x_error_t;
```
All functions return this.

----


#### xstr_t
```
typedef char ** xstr_t;
```

----

#### _xstr_t
```
typedef struct
{
	char * val;
	uint16_t cap;
	uint16_t len;
} * _xstr_t;
```

Internal representation of an xstr.


### Macros:

```
#define xstrlen(x)   (((_xstr_t) x)->len)
```
Get length of an xstring


### Functions:

```
x_error_t xstr_init(xstr_t * dest, uint16_t size);
```
Initializes an xstring

----

```
x_error_t str_init_set(xstr_t dest, char * src);
```
Initializes and sets an xstring

----

```
x_error_t xstr_cpy(xstr_t dest, xstr_t src);
```
Copies one xstring to another

----

```
x_error_t xstr_cpy_c(xstr_t dest, char * src);
```
Copies a C-string to an xstring

----

```
x_error_t xstr_cat(xstr_t dest, xstr_t src);
```
Append to an xstring

----

```
x_error_t xstr_cat_c(xstr_t dest, char * src);
```
Appends a C-string to an xstring.

----

```
x_error_t xstr_insert(xstr_t dest, xstr_t src, uint16_t index);
```
Inserts an xstring into another xstring at specified index

----

```
x_error_t xstr_insert_c(xstr_t dest, char * src, uint16_t index);
```
Inserts aa C-string into an xstring at specified index

----

```
x_error_t xstr_delete(xstr_t dest, uint16_t start, uint16_t end);
```
Deletes part of an xstring. (from index of start until end)

----

```
x_error_t xstr_push(xstr_t dest, char ch);
```
Appends a character to an xstring

----

```
x_error_t xstr_free(xstr_t src);
```
Deallocates an xstring
