#!/usr/bin/env bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 game_name"
	exit 1
fi

if [ ! -d $HOME/Games/$1 ]; then
	mkdir -p $HOME/Games/$1
fi

GAMEDIR=$HOME/Games/$1



export PATH=/opt/lunion-play-git/bin:$PATH

echo "Wine version: $(wine --version)"
read -rp "Proceed with this Wine version (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
	exit 1
fi

export WINEPREFIX=$GAMEDIR/windata
export WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe="

read -rp "Do you want create 32 bits prefix (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [yY] ]]; then
	export WINEARCH=win32
fi
read -rp "Do you want the debug Wine (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
	export WINEDEBUG=-all
fi

wineboot --init && wineserver --wait

if [ $? ]; then
	mkdir -p $GAMEDIR/shaders

	read -rp "Do you want install DXVK for Direct3D 9/10/11 (N/y) ? " _CONDITION;
	if [[ "$_CONDITION" =~ [yY] ]]; then
		$HOME/runtime/dxvk-1.8.1/setup_dxvk.sh install && wineserver --wait
	fi

	read -rp "Do you want install VKD3D Proton for Direct3D 12 (N/y) ? " _CONDITION;
	if [[ "$_CONDITION" =~ [yY] ]]; then
		mkdir -p $GAMEDIR/shaders

		$HOME/runtime/vkd3d-proton-master/setup_vkd3d_proton.sh install && wineserver --wait
	fi

	exit 0
fi

exit 1
