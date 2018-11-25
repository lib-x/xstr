if [ "$#" == 0 ]
then
	echo "Building..."
	$CC -Wall -Wextra src/str.c -c -o str.o
	echo "Done."
elif [ "$1" == "install" ]
then
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
	install xstr.h "/usr/local/include/libx/"
	echo "Done."
else
	echo "Usage: $0 <install>"
	exit 1
fi