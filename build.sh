#!/bin/sh

if [ -z "$CC" ]
then
	if type "cc" &> /dev/null
	then
		CC=cc
	elif type "clang" &> /dev/null
	then
		CC=clang
	elif type "gcc" &> /dev/null
	then
		CC=gcc
	elif type "tcc" &> /dev/null
	then
		CC=tcc
	else
		echo "Error: Failed to find a compiler"
		exit 1
	fi
fi

if [ "$#" == 0 ]
then
	echo "Building..."
	$CC -std=c90 -pedantic -Wall -Wextra -O3 src/str.c -c -o str.o
	echo "Done."
elif [ "$1" == "install" ]
then

	if [ ! -f "str.o" ]
	then
		echo "Error: Please run ./build.sh with no arguments to build before installing"
	fi

	echo "Checking for libx dirs"

	if [ ! -d "/usr/local/lib/libx" ]
	then
		mkdir "/usr/local/lib/libx"
	fi
	if [ ! -d "/usr/local/include/libx" ]
	then
		mkdir "/usr/local/include/libx"
	fi

	echo "Copying files"
	install xstr.o "/usr/local/lib/libx/"
	install src/xstr.h "/usr/local/include/libx/"
	echo "Done."
elif [ "$1" == "example" ]
then
	if [ ! -f "str.o" ]
	then
		echo "Error: Please run ./build.sh with no args to build before running example"
	fi

	$CC -Wall -Wextra example.c str.o
	./a.out
else
	echo "Usage: $0 <install|example>"
	exit 1
fi