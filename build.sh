if [ "$#" == 0 ]
then
	echo "Building..."
	$CC -Wall -Wextra src/str.c -c -o str.o
	echo "Done."
elif [ "$1" == "install" ]
then

	if [ ! -f "str.o" ]
	then
		echo "Please run ./build.sh with no arguments to build before installing"
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
		echo "Please run ./build.sh with no args to build before running example"
	fi

	$CC -Wall -Wextra example.c str.o
	./a.out
else
	echo "Usage: $0 <install|example>"
	exit 1
fi