AC_INIT([xstr], [2.0.2], [https://github.com/lib-x/xstr/issues],,[https://github.com/lib-x/xstr])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([subdir-objects foreign no-dependencies])
AC_PREREQ(2.69)
AC_CONFIG_HEADERS([src/config.h:src/config.in])
AC_CONFIG_MACRO_DIRS([build-aux/m4])

# $VERSION is assigned by AC_INIT (above), using the second argument
XSTR_MAJOR_VERSION=[`expr $VERSION : '\([0-9][0-9]*\)'`]
AC_SUBST(XSTR_MAJOR_VERSION)
XSTR_MINOR_VERSION=[`expr $VERSION : '[0-9][0-9]*\.\([0-9][0-9]*\)'`]
AC_SUBST(XSTR_MINOR_VERSION)
XSTR_MICRO_VERSION=[`expr $VERSION : '[0-9][0-9]*\.[0-9][0-9]*\.\([0-9][0-9]*\)'`]
AC_SUBST(XSTR_MICRO_VERSION)

# Don't add -g and -O2 by default
: ${CFLAGS=""}

# RELEASE TODO: set this to "no". Use `./configure --help | grep debug` to
# view the options. `./configure --enable-debug=no` will enable compiler
# optimizations, which usually are only be needed for a release.
AX_CHECK_ENABLE_DEBUG([yes])

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_FUNC( [strdup], [AC_DEFINE( [HAVE_STRDUP], [1], [Defined if strdup is present] )] )

# Use libtool to create shared library
LT_INIT

# This prevents problems such as those shown in
# https://github.com/theimpossibleastronaut/rmw/commit/90200c2df06b16f16b5d21d25c51966c0ee65b23#commitcomment-30291627
# and https://github.com/theimpossibleastronaut/rmw/issues/21
AM_MAINTAINER_MODE

# When ./configure is run, generate these makefiles
AC_CONFIG_FILES([	Makefile
									src/Makefile
									xstr.pc])
AC_OUTPUT
