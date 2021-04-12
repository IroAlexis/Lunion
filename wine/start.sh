#!/usr/bin/env bash

GAMEDIR=Games/game
PATH=/opt/lunion-play-git/bin/:$PATH

export WINEPREFIX=$HOME/$GAMEDIR/windata/
export WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe="
export WINEDEBUG=-all

echo "[+] lunion-play: game: preparing to launch..."
wineboot &> /dev/null && wineserver --wait

unset WINEDLLOVERRIDES
unset WINEDEBUG

export WINEDLLOVERRIDES="winemenubuilder.exe="
#export WINEESYNC=1
export WINEFSYNC=1
#export WINE_DISABLE_FAST_SYNC=1
export WINEDEBUG=fixme-all
#export WINEDEBUG=-all


# DXVK
#export DXVK_HUD=devinfo,fps,version,api
#export DXVK_HUD=full
export DXVK_LOG_LEVEL=none

#VKD3D
export VKD3D_DEBUG=none
export VKD3D_CONFIG=dxr,force_static_cbv,multi_queue

export __GL_SHADER_DISK_CACHE=1
export __GL_SHADER_DISK_CACHE_SKIP_CLEANUP=1
export __GL_SHADER_DISK_CACHE_PATH=$HOME/$GAMEDIR/shaders

export MANGOHUD_CONFIGFILE=$HOME/Games/mangohud.config


# Prevention en reference au probleme que j'ai eu avec The Witcher 3
cd $HOME/$GAMEDIR/windata/drive_c/

echo "[+] lunion-play: game: launch the game..."
wine gameexe.exe && wineserver --wait
#wine64 gameexe.exe && wineserver --wait
