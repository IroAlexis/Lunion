#!/usr/bin/env bash

source "$(dirname $0)"/customization.cfg

msg()
{
  echo -e " \033[1;34m->\033[1;0m \033[1;1m$1\033[1;0m" >&2
}

dialog()
{
  echo -e "\033[1;34m::\033[1;0m \033[1;1m$1\033[1;0m" >&2
}

warning()
{
  echo -e "\033[1;31m==> WARNING: $1\033[1;0m" >&2
}

error()
{
  echo -e "\033[1;31m==> ERROR:\033[1;0m \033[1;1m$1\033[1;0m" >&2
}



# ==============
#  Verification
# ==============

if [ "$#" -gt 2 ]; then
  echo "Usage: $0 game_name [/path/to/setup_exe]"
  exit 1
fi

if [[ "$1" =~ ^\/$|(\/[a-zA-Z_0-9-]+)+$ ]]; then
  error "You don't must not be a path ($1)"
  echo ""
  exit 1
fi


# ============================
#  Games folder Configuration
# ============================

dialog "Do you want install the game in $_games_path ?"
read -rp "> N/y : " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
  msg "Please set \`_game_path\` as you want in $(basename $0)"
  exit 1
fi
if [ ! -d "$_games_path/$1" ]; then
  mkdir -p "$_games_path/$1"
fi


# ====================
#  Wine Configuration
# ====================

if [ ! -z "$_CUSTOM_WINE" ]; then
  if [ -z "$PATH" ]; then
    export PATH="$_CUSTOM_WINE"
  else
    export PATH="$_CUSTOM_WINE:$PATH"
  fi

  if [ -z "$LD_LIBRARY_PATH" ]; then
    export LD_LIBRARY_PATH="$_CUSTOM_WINE/../lib64:$_CUSTOM_WINE/../lib32:$_CUSTOM_WINE/../lib"
  else
    export LD_LIBRARY_PATH="$_CUSTOM_WINE/../lib64:$_CUSTOM_WINE/../lib32:$_CUSTOM_WINE/../lib:$LD_LIBRARY_PATH"
  fi
fi


echo "[+] info:: lunion-play: $(wine --version)"
dialog "Proceed with this Wine version ?"
read -rp "> N/y : " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
  msg "Please set \`_CUSTOM_WINE\` as you want in $(basename $0)"
  exit 1
fi


# ==========================
#  Wine prefix Installation
# ==========================

GAME=$_games_path/$1

export WINEPREFIX=$GAME/pfx
export WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe="

dialog "Do you want use 32 bits prefix ?"
read -rp "> N/y : " _CONDITION;
if [[ "$_CONDITION" =~ [yY] ]]; then
  export WINEARCH=win32
fi
dialog "Do you want the debug Wine ?"
read -rp "> N/y : " _CONDITION;
if [[ "$_CONDITION" =~ [nN] ]]; then
  export WINEDEBUG=-all
fi

wineboot --init && wineserver --wait


# ================================
#  Translation layer Installation
# ================================
if [ "$?" ]; then
  mkdir -p $GAME/shaders

  dialog "Do you want install DXVK for Direct3D 9/10/11 ?"
  read -rp "> n/y : " _CONDITION;
  if [[ "$_CONDITION" =~ [yY] ]]; then
    "$_dxvk_path"/setup_dxvk.sh install && wineserver --wait
  fi

  dialog "Do you want install VKD3D Proton for Direct3D 12 ?"
  read -rp "> n/y : " _CONDITION;
  if [[ "$_CONDITION" =~ [yY] ]]; then
    "$_vkd3dproton_path"/setup_vkd3d_proton.sh install && wineserver --wait
  fi


  # ===================
  #  Game Installation
  # ===================
  if [ "$2" ]; then
    if [ ! -f "$2" ]; then
      exit 1
    fi

    dialog "Is it a GOG installer ?"
    read -rp "> n/y : " _CONDITION
    if [[ "$_CONDITION" =~ [yY] ]]; then
      dialog "Do you want the GUI ?"
      read -rp "> n/y : " _CONDITION
      if [[ "$_CONDITION" =~ [nN] ]]; then
        _ARGS="/SP- /SUPPRESSMSGBOXES"

        dialog "Do you want a silent installation without progress bar ?"
        read -rp "> n/y : " _CONDITION
        if [[ "$_CONDITION" =~ [yY] ]]; then
          _ARGS="$_ARGS /VERYSILENT"
        else
          _ARGS="$_ARGS /SILENT"
        fi

        dialog "Do install the game outside the wine prefix ?"
        read -rp "> n/y : " _CONDITION
        if [[ "$_CONDITION" =~ [yY] ]]; then
          mkdir -p $GAME/gamedata
          _ARGS="$_ARGS DIR=\"$(winepath -w $GAME/gamedata)\""
          warning "Some installers completely ignore this feature. Check $(winepath -u c:\\GOG\ Games)"
        fi
      fi
    fi

    warning "Don't launch the game with the installer..."
    if [ ! -z "$_ARGS" ]; then
      wine "$2" $_ARGS && wineserver --wait
    else
      wine "$2" && wineserver --wait
    fi
  fi

  msg "exit script done"
  echo ""
  exit 0
fi

exit 1
