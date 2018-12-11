AM_CFLAGS = -std=c90 -pedantic -Wall -Wextra

libxstr_la_SOURCES = str.c
include_HEADERS = str.h

lib_LTLIBRARIES = libxstr.la

libxstr_la_LDFLAGS = -version-info $(XSTR_MAJOR_VERSION):$(XSTR_MINOR_VERSION):$(XSTR_MICRO_VERSION)
libxstr_la_LDFLAGS += ${extra_ldflags}
