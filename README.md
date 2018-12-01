# xstr: A simpler string library

![License](https://img.shields.io/badge/License-Public%20Domain-brightgreen.svg?style=for-the-badge&link=https://github.com/lib-x/xstr/blob/master/LICENSE)
![Codacy](https://img.shields.io/codacy/grade/:7dd9c8b220d9406d8dddaf4b29f153d4.svg?style=for-the-badge)


## Why to use this over other string libraries

-  It's public domain
-  You can access the internal string using `*str` instead of having to do `get_val(str)` or `str.val`
-  Mostly compatible with C90/C89, not just C99
-  Consistent, simple error handling.  All functions return an `x_error_t`.

## Why not to use this library

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

```
mkdir deps deps/xstr
git clone https://github.com/the-sushi/xstr.git /tmp/xstr
cp /tmp/xstr/src/* deps/xstr/
```

### If you like this lib enough to install it everywhere

```
git clone https://github.com/the-sushi/xstr.git
cd xstr
./build.sh
./build.sh install
```

## Example:

```
#include <lib-x/str.h>
#include <stdio.h>

int main(void)
{
	xstr_t thing = NULL;
	x_error_t e;

	e = xstr_init_set(&thing, "hello");
	if (e != XE_NONE) return 1;

	e = xstr_cat_c(thing, " world");
	if (e != XE_NONE) return 1;

	printf("Before substitution: %s\n", *thing);

	e = xstr_delete(thing, 0, 4);
	if (e != XE_NONE) return 1;

	e = xstr_insert_c(thing, "Hi there,", 0);
	if (e != XE_NONE) return 1;

	printf("After substitution: %s\n", *thing);

	e = xstr_push(thing, '!');
	if (e != XE_NONE) return 1;

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
	XE_OVERFLOW,
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

#### _xstr_s
```
typedef struct _xstr_s
{
	char * val;
	size_t cap;
	size_t len;
};
```

Internal representation of an xstr.


### Macros:

```
#define xstrlen(x)   (((_xstr_s *) x)->len)
```
Get length of an xstring

```
#define xstr_init_set(dest, src)         xstr_init_set_n((dest), (src), strlen(src))
```
Initializes an xstring with specified C-string value

```
#define xstr_cpy_c(dest, src)            xstr_cpy_c_n((dest), (src), strlen(src))
```
Copies specfied C-string to specified xstring

```
#define xstr_cat_c(dest, src)            xstr_cat_c_n((dest), (src), strlen(src))
```
Appends specified C-string to specified xstring

```
#define xstr_insert_c(dest, src, index)  xstr_insert_c_n((dest), (src), index, strlen(src))
```
Inserts specified C-string into xstring at specified location

### Functions:

```
x_error_t xstr_init(xstr_t * dest, size_t size);
```
Initializes an xstring

----

```
x_error_t str_init_set_n(xstr_t * dest, char * src, size_t len);
```
Initializes and sets an xstring to `src`, assuming `src` is `len` chars long

----

```
x_error_t xstr_cpy(xstr_t dest, xstr_t src);
```
Copies one xstring to another

----

```
x_error_t xstr_cpy_c_n(xstr_t dest, char * src, size_t len);
```
Copies a C-string that is `len` chars long into an xstring

----

```
x_error_t xstr_cat(xstr_t dest, xstr_t src);
```
Append an xstring to an xstring

----

```
x_error_t xstr_cat_c_n(xstr_t dest, char * src, size_t len);
```
Appends a C-string that is `len` chars long into an xstring.

----

```
x_error_t xstr_insert(xstr_t dest, char * src, size_t index);
```
Inserts an xstring into another xstring at specified index
---

```
x_error_t xstr_insert_c_n(xstr_t dest, char * src, size_t index, size_t len);
```
Inserts a C-string that is `len` chars long into an xstring at specified index

----

```
x_error_t xstr_delete(xstr_t dest, size_t start, size_t end);
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
