# xstr: A simpler string library

[![License](https://img.shields.io/badge/License-Public%20Domain-brightgreen.svg?style=flat)](https://github.com/lib-x/xstr/blob/master/LICENSE)
[![Codacy](https://api.codacy.com/project/badge/Grade/7dd9c8b220d9406d8dddaf4b29f153d4)](https://www.codacy.com/app/joshpritsker/xstr?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=lib-x/xstr&amp;utm_campaign=Badge_Grade)

## What is this:

xstr is a library for managing and manipulating dynamic strings in a simple way.

## Why use this over other string libraries:

-  It's public domain
-  You can access the internal string using `*str` instead of having to do `get_val(str)` or `str.val`
-  Mostly compatible with C90/C89, not just C99
-  Consistent, simple interface.  All functions take `dest` as the first argument and return an `x_error_t`.

## Why not to use this library:

-  You don't have libc available
-  You're using a custom allocator
-  You're have no allocator
-  You need *really* high performance
-  You're a programming-masochist
-  You're using Python

## How to get it:

### If you have clib:

`clib install the-sushi/xstr`

### If you don't have clib:
Either get clib, or do this:

```bash
mkdir deps deps/xstr
git clone https://github.com/the-sushi/xstr.git /tmp/xstr
cp /tmp/xstr/src/* deps/xstr/
```

### If you like this lib enough to install it everywhere

```bash
git clone https://github.com/the-sushi/xstr.git
cd xstr
./build.sh
./build.sh install
```

## Example:

### Without any error handling:

```c
#include <lib-x/str.h>
#include <stdio.h>

int main(void)
{
	xstr_t thing;

	xstr_init_set(&thing, "hello");
	xstr_cat_c(thing, " world");

	printf("Before substitution: %s\n", *thing);

	xstr_delete(thing, 0, 4);
	xstr_insert_c(thing, "Hi there,", 0);

	printf("After substitution: %s\n", *thing);

	xstr_push(thing, '!');

	printf("After push: %s\n", *thing);

	return 0;
}
```

### With basic example error handling:

```c
#include <lib-x/str.h>
#include <stdio.h>

int main(void)
{
	xstr_t thing;
	x_error_t e;

	e = xstr_init_set(&thing, "hello");
	if (error != XE_NONE) return 1;

	e = xstr_cat_c(thing, " world");
	if (error != XE_NONE) return 1;

	printf("Before substitution: %s\n", *thing);

	e = xstr_delete(thing, 0, 4);
	if (error != XE_NONE) return 1;

	e = xstr_insert_c(thing, "Hi there,", 0);
	if (error != XE_NONE) return 1;

	printf("After substitution: %s\n", *thing);

	e = xstr_push(thing, '!');
	if (error != XE_NONE) return 1;

	printf("After push: %s\n", *thing);

	return 0;
}
```

### Case/Switch error handling:

```c
#include <lib-x/str.h>
#include <stdio.h>

int main(void)
{
	xstr thing;
	x_error_t e;

	e = xstr_init_set(&thing, "Hello, world!");
	switch (e)
	{
		case XE_NONE:
			break;
		case XE_ALLOC:
			perror("Error allocating string");
			return 1;
		default:
			fprintf(stderr, "Unknown error.  This should not be happening");
			return 1;
	}

	puts(*thing);
	return 0;
}
```

## API:

### Types:

#### x_error_t
```c
typedef enum
{
	XE_NONE,
	XE_ALLOC,
	XE_DUP,
	XE_NORANGE,
	XE_OVERFLOW,
	XE_ISNULL
} x_error_t;
```
All functions return this.

----


#### xstr_t
```c
typedef char ** xstr_t;
```

----

#### _xstr_s
```c
typedef struct _xstr_s
{
	char * val;
	size_t cap;
	size_t len;
};
```

Internal representation of an xstr.


### Macros:

```c
#define xstrlen(x)   (((_xstr_s *) x)->len)
```
Get length of an xstring

```c
#define xstr_init_set(dest, src)         xstr_init_set_n((dest), (src), strlen(src))
```
Initializes an xstring with specified C-string value

```c
#define xstr_cpy_c(dest, src)            xstr_cpy_c_n((dest), (src), strlen(src))
```
Copies specfied C-string to specified xstring

```c
#define xstr_cat_c(dest, src)            xstr_cat_c_n((dest), (src), strlen(src))
```
Appends specified C-string to specified xstring

```c
#define xstr_insert_c(dest, src, index)  xstr_insert_c_n((dest), (src), index, strlen(src))
```
Inserts specified C-string into xstring at specified location

### Functions:

```c
x_error_t xstr_init(xstr_t * dest, size_t size);
```
Initializes an xstring

----

```c
x_error_t str_init_set_n(xstr_t * dest, char * src, size_t len);
```
Initializes and sets an xstring to `src`, assuming `src` is `len` chars long

----

```c
x_error_t xstr_cpy(xstr_t dest, xstr_t src);
```
Copies one xstring to another

----

```c
x_error_t xstr_cpy_c_n(xstr_t dest, char * src, size_t len);
```
Copies a C-string that is `len` chars long into an xstring

----

```c
x_error_t xstr_cat(xstr_t dest, xstr_t src);
```
Append an xstring to an xstring

----

```c
x_error_t xstr_cat_c_n(xstr_t dest, char * src, size_t len);
```
Appends a C-string that is `len` chars long into an xstring.

----

```c
x_error_t xstr_insert(xstr_t dest, char * src, size_t index);
```
Inserts an xstring into another xstring at specified index
---

```c
x_error_t xstr_insert_c_n(xstr_t dest, char * src, size_t index, size_t len);
```
Inserts a C-string that is `len` chars long into an xstring at specified index

----

```c
x_error_t xstr_delete(xstr_t dest, size_t start, size_t end);
```
Deletes part of an xstring. (from index of start until end)

----

```c
x_error_t xstr_push(xstr_t dest, char ch);
```
Appends a character to an xstring

----

```c
x_error_t xstr_free(xstr_t src);
```
Deallocates an xstring
