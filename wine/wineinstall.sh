#!/usr/bin/env sh

export GAMEDIR=$HOME/Games

if [ $# -ne 1 ]; then
	echo "Usage: $0 game_name"
	exit 1
fi

if [ ! -d $GAMEDIR/$1 ]; then
	echo "$GAMEDIR/$1 doesn't exist"
	exit 1
fi



export PATH=/opt/lunion-play-git/bin:$PATH

echo "Wine version: $(wine --version)"
read -rp "Proceed with this Wine version (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
	exit 1
fi

export WINEPREFIX=$GAMEDIR/$1/windata
export WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe="
read -rp "Install 32 bit (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [yY] ]]; then
	export WINEARCH=win32
fi
read -rp "Do you want the debug Wine (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
	export WINEDEBUG=-all
fi

wineboot --init

# wineserver still alive approx 5s after
echo "Waiting wineserver..."
wineserver --wait




read -rp "Do you want install DXVK for Direct3D 9/10/11 (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [yY] ]]; then
	$HOME/Downloads/runtime/dxvk-1.7.3/setup_dxvk.sh install
	wineserver --wait
fi

read -rp "Do you want install VKD3D Proton for Direct3D 12 (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [yY] ]]; then
	$HOME/Downloads/runtime/vkd3d-proton-master/setup_vkd3d_proton.sh install
	wineserver --wait
fi



#export WINEDLLOVERRIDES="winemenubuilder.exe="
#wine $2

# Confirm that wineserver is killed
#wineserver --wait


exit 0
