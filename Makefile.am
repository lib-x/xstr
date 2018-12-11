packextrasdir=@docdir@
SUBDIRS = src
EXTRA_DIST =	\
	README.md	\
	LICENSE	\
	package.json

packextras_DATA=$(EXTRA_DIST)

ACLOCAL_AMFLAGS = --install -I build-aux/m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = xstr.pc
