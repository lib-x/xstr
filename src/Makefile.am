AM_CFLAGS = -std=c89 -pedantic -Wall -Wextra

lib_LTLIBRARIES = libxstr.la

libxstr_la_SOURCES = str.c
include_HEADERS = str.h
libxstr_la_LDFLAGS = -version-info $(XSTR_MAJOR_VERSION):$(XSTR_MINOR_VERSION):$(XSTR_MICRO_VERSION)
libxstr_la_LDFLAGS += ${extra_ldflags}

# Build the example program
example_CFLAGS = $(AM_CFLAGS)
EXTRA_PROGRAMS = example
example_SOURCES = example.c
example_DEPENDENCIES = libxstr.la
example_LDFLAGS = -all-static -L@top_builddir@/src/.libs
example_LDADD = -lxstr
