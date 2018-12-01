# xstr: A simpler string library


## Why to use this over other string libraries

- It's public domain
- You can access the internal string using `*str` instead of having to do `get_val(str)` or `str.val`
- Mostly compatible with C90/C89, not just C99
- Consistent, simple error handling.  All functions return an `x_error_t`.

## Why not to use this library

- You don't have libc available
- You're using a custom allocator
- You're have no allocator
- You need *really* high performance
- You're a programming-masochist
- You're using Python

## How to get it:

### If you have clib:

`clib install the-sushi/xstr`

### If you don't have clib:
Either get clib, or do this:

```
mkdir deps deps/xstr
git clone https://github.com/the-sushi/xstr.git /tmp/xstr
cp /tmp/xstr/src/str.c deps/xstr/str.c
cp /tmp/xstr/src/str.h deps/xstr/str.h
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

#### _xstr_t and _xstr_s
```
typedef struct _xstr_s
{
	char * val;
	size_t cap;
	size_t len;
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
x_error_t xstr_init(xstr_t * dest, size_t size);
```
Initializes an xstring

----

```
x_error_t str_init_set(xstr_t * dest, char * src);
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
#define xstr_insert(x, y, z)  xstr_insert_c(x, *(y), z)
```
Inserts an xstring into another xstring at specified index

----

```
x_error_t xstr_insert_c(xstr_t dest, char * src, size_t index);
```
Inserts aa C-string into an xstring at specified index

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
