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

example$(EXEEXT): $(example_OBJECTS) $(example_DEPENDENCIES)
	$(LINK) $(example_LDFLAGS) $(example_OBJECTS) $(example_LDADD)
	file=example;	\
	if test -f $$file; then	\
		mv $$file $(top_builddir)/$$file;	\
	fi

clean-local:
	file=$(top_builddir)/example; \
	if test -f $$file; then \
		rm $$file; \
	fi
