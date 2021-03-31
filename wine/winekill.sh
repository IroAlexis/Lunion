#!/usr/bin/env bash

arg="$1"
wine="$2"

export WINEPREFIX="$arg"

if [ -n "$wine" ] && [ -n "$arg" ]
then
	export PATH="$wine":$PATH

	wineserver -k
	echo "$arg has stoppped"
elif [ -n "$arg" ]
then
	wineserver -k
	echo "$arg has stoppped"
else
	echo "Usage: $0 /path/to/wineprefix [ /path/to/wine/bin ] "
	echo "  /path/to/wine/bin is optionnal"
	exit 1
fi

wineserver --wait
exit 0

