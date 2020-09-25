Lunion
======
A game library for all your PC games under Linux. Fully ergonomic for beginners but also customizable for experts (we're going to try to work with you to offer you that opportunity)



Table of Contents
-----------------
1. [Introduction](#introduction)
2. [Problematic](#problematic)
3. [How it works](#how-it-works)
4. [Features](#features)
5. [File organisation](#file-organisation)
6. [Windows games tested](#windows-games-tested)
7. [Useful environment variables](#useful-environment-variables)
8. [Tips and tricks](#tips-and-tricks)
9. [Guides](#guides)
10. [Acknowledgements](#acknowledgements)
11. [Licence](#licence)



Introduction
------------
Inspired by Lutris, Steam and GOG Galaxy (2.0), Lunion is an open source GTK application that allows you to bring together all your Linux and/or Windows games (DRM-free ideally) in a single place.
You can import your games list, install and launch your favorite PC games. You don't have to worry about how to organize your game files. However, it is fully configurable if you can get your hands dirty



Problematic
-------------
**(*W.I.P.*)**



How it works
------------
For the native games, Lunion detects if you have installed with your package manager and integrates them in the library. It integrates also emulator applications and compatibility layers:
* ~~melonDS, open source emulator to run the DS/DSi games~~
* Wine (and/or Lunion Play alias Wine TkG), a open source compatibility layer capable of running Windows applications on several POSIX-compliant operating systems, such as Linux, macOS, & BSD
* DXVK, a open source Vulkan-based translation layer for Direct3D 9/10/11 which allows running 3D applications on Linux using Wine



System requirements (Recommended)
---------------------------------
* *OS*: Linux kernel with [Fsync patch](https://wiki.archlinux.org/index.php/Steam#Fsync_patch)
* *Processor*: Multi core 64 bits
* *Memory*: +8 Go RAM
* *Graphic*: Vulkan 1.1
* *Storage*: SSD

### Dependencies
* curl
* gtk
* unzip
* winetricks
* vkd3d-proton

### Troubleshooting
* **[EXPERIMENTAL]** For the configuration of 8 Go RAM, with DXVK, he is possible that you have an error `DxvkMemoryAllocator: Memory allocation failed`. You can use this procedure ([here](https://www.reddit.com/r/linux_gaming/comments/em97io/regarding_the_dxvkmemoryallocator_memory)) but read the comments please.




Features
--------
### Planned
* Display the installed runners (*and others...*) and can them uninstall easly
* Using XML for the configuration file: `.conf`
* [GOG.com] Support of DLCs installation option

### No tested
* Multi-monitor



File organisation
-----------------
Data `$HOME/.local/share/lunion/`
* `games` : Installed games location (default folder but you have choice)
* `log` : Storing Lunion and/or Lunion Play log files location (disable by default)
* `runtime` : Location of DXVK and others...


Cache `$HOME/.cache/lunion/`
* `download` : Files download location
* `tmp` : Temporary files location


Configuration `$HOME/.config/lunion/`
* `games` : Games configuration (banner pictures, logo, ...)



Windows games tested
--------------------
***Not regulary update for the moment***

**Stable:**
* A Plague Tale: Innocence (random issue on Nvidia cards)
* Control Ultimate Edition
* Children of Morta
* Dead Cells
* Frostpunk
* Katana ZERO
* Metro 2033 Redux
* Metro: Last Night Redux
* Metro Exodus
* Minecraft Dungeons (requires [mf-install](https://github.com/z0z0z/mf-install))
* Ori and the Blind Forest: Definitive Edition
* The Witcher 3: Wild Hunt GOTY

**Instable:**
* Legends of Runeterra (disconnection possible)

**Failure:**
* League of Legends/Teamfight Tactics (Patch 10.19 since 24/09/2020)
* Valorant (incompatibility with Vanguard [for the moment](https://www.winehq.org/announce/5.8))

**Future:**
* Cyberpunk 2077
* Hytale
* No Man's Sky
* Project F
* The Last Nigth



Useful environment Variables 
----------------------------
### Wine
| Environment Variables | Value(s) | Description |
| :------------------- | :----: | :---------- |
| `STAGING_SHARED_MEMORY` | `1` or `0` |  |
| `WINE_LARGE_ADDRESS_AWARE` | `1` or `0` | Useful for 32-bit games hitting address space limitations, only with Lunion Play (or a build of [Wine TkG](https://github.com/Tk-Glitch/PKGBUILDS/tree/master/wine-tkg-git)) but enable by default |

### Proprietary driver NVIDIA
| Environment Variables | Value(s) | Description |
| :------------------- | :----: | :---------- |
| `__GL_NextGenCompiler` | `1` or `0` | Using the Vulkan SPIR-V Compiler. The goal is to reduce shader compilation time and shader system memory consumption |
| `__GL_SHADER_DISK_CACHE` | `1` or `0` |  |
| `__GL_SHADER_DISK_CACHE_PATH` | `$PATH/TO/` |  |
| `__GL_SHADER_DISK_CACHE_SKIP_CLEANUP` | `1` or `0` | Remove the shader cache size limit that is 125Mb (NB: disable this limit with the value `1`) (source from [Nvidia Forum](https://forums.developer.nvidia.com/t/opengl-shader-disk-cache-max-size-garbage-collection/60056))|
| `__GL_SHOW_GRAPHICS_OSD` | `1` or `0` | Showing the Graphics API Visual Indicator and FPS |
| `__GL_THREADED_OPTIMIZATION` | `1` or `0` | For the OpenGL games, allow the driver NVIDIA to work multi threaded. This speeds up when the drivers has a lot to do, but when your CPU is filled to the max, it can lower fps (Enable by default when the driver thinks it can improve performance) |

### Open-source driver Mesa
There is a full list of environment variables available [here](https://www.mesa3d.org/envvars.html).

| Environment Variables | Value(s) | Description |
| :------------------- | :----: | :---------- |
| `GALLIUM_HUD` | `fps` | Showing Overlay FPS |
| `RADV_PERFTEST` | `aco` | For the AMD GPU users, ACO is an open-source shader compiler developed by Valve. It offers lesser compilation time and also provides more FPS (source from [Phoronix](https://www.phoronix.com/scan.php?page=article&item=radv-aco-llvm&num=1)) |
| `mesa_glthread` | `true` or `false` | [Performance](https://www.gamingonlinux.com/wiki/Performance_impact_of_Mesa_glthread) and [amelioration with Mesa 20.0](https://www.phoronix.com/scan.php?page=news_item&px=Faster-Emulators-Mesa-GL-Thread) |



Tips and tricks
---------------
* **Change Windows version : `winecfg /v win10` requires Wine 5.7+**
* Media Foundation workaround for Wine: https://github.com/z0z0z/mf-install or https://github.com/z0z0z/mf-installcab
* Freeze Wine, use this commande: `WINEPREFIX=/path/to/prefix/ /path/to/wineserver -k`
* Using winetricks without GUI: `winetricks -q`
* Using winetricks with an other Wine's version: add the environment variable `WINE=/path/to/wine`
* DXVK installation with a specific Wine's version: add `/opt/wine/bin:$PATH` in `$PATH`
* When updating the Wine prefix, prevent the installation request of Wine Mono and Wine Gecko: add the environment variable `WINEDLLOVERRIDES="mscoree,mshtml=d"`
* [GOG.com] Silent installater, add `/VERYSILENT /SUPPRESSMSGBOXES /NORESTART /SP-` (don't work with: The Witcher 3 GOTY)
* Disabling NVAPI (NVIDIA's core software development kit that allows direct access to NVIDIA GPUs and drivers on Windows) required on some games (Uplay, Battle.Net, etc): `WINEDLLOVERRIDES="nvapi,nvapi64=d"`




Guides
------
* [Improving gaming performance](https://www.reddit.com/r/linux_gaming/comments/e32v49/improving_gaming_performance_guide/)
* [NVIDIA: Reduce stuttering](https://www.reddit.com/r/wine_gaming/comments/8ih53x/tutorial_how_to_reduce_stuttering_nvidia/)



Acknowledgements
----------------
* [Wine](https://winehq.org) 
* [Tk-Glitch](https://github.com/Tk-Glitch)
* [Philip Rebohle](https://github.com/doitsujin)
* [Joshua Ashton](https://github.com/Joshua-Ashton)
* [Lutris](https://github.com/lutris)
* [GameHub](https://github.com/tkashkin/GameHub)
* [CD Projekt RED](https://en.cdprojektred.com)
* Valve [Proton](https://github.com/ValveSoftware/Proton)




Licence
-------
Available in [LICENSE](LICENSE) file<br>

**Copyright (C)** 2019-2020 Alexis Peypelut alias IroAlexis
