#!/usr/bin/env bash

# ==============
#  Verification
# ==============
if [ "$#" -gt 2 ]; then
  echo "Usage: $0 game_name [/path/to/setup_exe]"
  exit 1
fi

if [[ "$1" =~ ^\/$|(\/[a-zA-Z_0-9-]+)+$ ]]; then
  echo "\`$1\` don't must not be a path"
  exit 1
elif [ ! -d "$HOME/Games/$1" ]; then
  mkdir -p $HOME/Games/$1
fi


# ==========================
#  Wine prefix Installation
# ==========================
export GAMEDIR=$HOME/Games/$1

export WINEBINDIR=/opt/lunion-play-git/bin
export PATH=$WINEDIR:$PATH
export LD_LIBRARY_PATH=$WINEDIR/../lib64:$WINEDIR/../lib32:$WINEDIR/../lib:$LD_LIBRARY_PATH

echo "Wine version: $(wine --version)"
read -rp "Proceed with this Wine version (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
  exit 1
fi

export WINEPREFIX=$GAMEDIR/pfx
export WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe="

read -rp "Do you want use 32 bits prefix (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [yY] ]]; then
  export WINEARCH=win32
fi
read -rp "Do you want the debug Wine (N/y) ? " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
  export WINEDEBUG=-all
fi

wineboot --init && wineserver --wait


# ================================
#  Translation layer Installation
# ================================
if [ "$?" ]; then
  mkdir $GAMEDIR/shaders

  read -rp "Do you want install DXVK for Direct3D 9/10/11 (N/y) ? " _CONDITION;
  if [[ "$_CONDITION" =~ [yY] ]]; then
    $HOME/runtime/dxvk-1.8.1/setup_dxvk.sh install && wineserver --wait
  fi

  read -rp "Do you want install VKD3D Proton for Direct3D 12 (N/y) ? " _CONDITION;
  if [[ "$_CONDITION" =~ [yY] ]]; then
    $HOME/runtime/vkd3d-proton-master/setup_vkd3d_proton.sh install && wineserver --wait
  fi


  # ===================
  #  Game Installation
  # ===================
  if [ "$2" ]; then
    if [ ! -f "$2" ]; then
      exit 1
    fi

    read -rp "Is it a GOG installer (n/y) ? " _CONDITION
    if [[ "$_CONDITION" =~ [yY] ]]; then
      read -rp "Do you want a gui (n/y) ? " _CONDITION
      if [[ "$_CONDITION" =~ [nN] ]]; then
        ARGS="/SP- /SUPPRESSMSGBOXES"

        read -rp "Do you want a silent installation without progress bar (n/y) ? " _CONDITION
        if [[ "$_CONDITION" =~ [yY] ]]; then
          ARGS="$ARGS /VERYSILENT"
        else
          ARGS="$ARGS /SILENT"
        fi

        read -rp "Do install the game outside the wine prefix (n/y) ? " _CONDITION
        if [[ "$_CONDITION" =~ [yY] ]]; then
          mkdir $GAMEDIR/gamedata
          ARGS="$ARGS DIR=\"$(winepath -w $GAMEDIR/gamedata)\""
        fi
      fi
    fi

    if [ ! -z "$ARGS" ]; then
      wine "$2" $ARGS && wineserver --wait
    else
      wine "$2" && wineserver --wait
    fi
  fi

  exit 0
fi

exit 1
