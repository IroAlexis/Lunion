#!/usr/bin/env bash


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
#
# Set to the path if you want install your games somewhere else
# Example: _games_path="/home/frog" will install your game in /home/frog/game_name
_games_path="$HOME/Games"

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
#
# Custom Wine dir - Comment the line to use system wine
# Example: _CUSTOM_WINE="/opt/wine-tkg-git/bin"
_CUSTOM_WINE="/opt/lunion-play-git/bin"

export PATH=$_CUSTOM_WINE:$PATH
export LD_LIBRARY_PATH=$_CUSTOM_WINE/../lib64:$_CUSTOM_WINE/../lib32:$_CUSTOM_WINE/../lib:$LD_LIBRARY_PATH


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
    $HOME/runtime/dxvk-1.8.1/setup_dxvk.sh install && wineserver --wait
  fi

  dialog "Do you want install VKD3D Proton for Direct3D 12 ?"
  read -rp "> n/y : " _CONDITION;
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
        fi
      fi
    fi

    warning "Don't launch the game with the setup..."
    if [ ! -z "$_ARGS" ]; then
      wine "$2" $_ARGS && wineserver --wait
    else
      wine "$2" && wineserver --wait
    fi
  fi

  msg "exit setup done"
  echo ""
  exit 0
fi

exit 1
