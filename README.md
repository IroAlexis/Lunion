Lunion
======
A game library for all your PC games under Linux (GTK) inspired by GameHub, Steam and GOG Galaxy. Try to be ergonomic for "beginners" but also customizable for experts (we're going to try to work with you to offer you that opportunity)

The Windows games tested list is available [here](https://github.com/IroAlexis/lunion-play/wiki/Home) :frog:



Table of Contents
-----------------
1. [How it works](#how-it-works)
2. [File organisation](#file-organisation)
3. [Useful environment variables](#useful-environment-variables)
4. [Tips and tricks](#tips-and-tricks)
5. [Guides](#guides)
6. [Troubleshooting](#troubleshooting)
7. [Acknowledgements](#acknowledgements)
8. [Licence](#licence)



How it works
------------
For the native games, Lunion detects if you have installed with your package manager and integrates them in the library. It integrates also emulator applications and compatibility layers:
* [Wine](https://www.winehq.org/), a open source compatibility layer capable of running Windows applications on several POSIX-compliant operating systems, such as Linux, macOS, & BSD
* [DXVK](https://github.com/doitsujin/dxvk), a open source Vulkan-based translation layer for Direct3D 9/10/11 which allows running 3D applications on Linux using Wine
* [VKD3D-Proton](https://github.com/HansKristian-Work/vkd3d-proton), a fork of [VKD3D](https://source.winehq.org/git/vkd3d.git/), which aims to implement the full Direct3D 12 API on top of Vulkan

How Lunion install and launch your games, you can know him [here](https://github.com/IroAlexis/lunion/blob/master/lunion-play.md). It can also be useful for know the Wine functioning.



System requirements (Recommended)
---------------------------------
* *OS*: Linux kernel
* *Processor*: Multi core 64 bits
* *Memory*: +8 Go RAM
* *Graphic*: Vulkan 1.1
* *Storage*: SSD

### Dependencies
* curl
* gtk4
* libadwaita-git
* libzip
* sqlite3
* wine/wine-staging (*optionnal*)
* winetricks (*optionnal*)
* vkd3d (*optionnal*)



File organisation
-----------------
Data `$HOME/.local/share/lunion/`
* `games` : Installed games location (default folder but you have choice)
* `logs` : Storing Lunion and/or Lunion Play log files location (disable by default)
* `runtime` : Location of DXVK and VKD3D Proton
* `tools` : Location of Lunion Play and Wine TkG


Cache `$HOME/.cache/lunion/`
* `download` : Files download location
* `tmp` : Temporary files location


Configuration `$HOME/.config/lunion/`
* `plateform` : Relative to the plateform connexion



Useful environment Variables 
----------------------------
### Wine
| Environment Variables | Value(s) | Description |
| :------------------- | :----: | :---------- |
| `STAGING_SHARED_MEMORY` | `1` or `0` |  |
| `WINE_LARGE_ADDRESS_AWARE` | `1` or `0` | Useful for 32-bit games hitting address space limitations, only with [Lunion Play](https://github.com/IroAlexis/lunion-play-build/tree/lunion-play) (or a build of [Wine TkG](https://github.com/Frogging-Family/wine-tkg-git)) but enable by default |

### Proprietary driver NVIDIA
| Environment Variables | Value(s) | Description |
| :------------------- | :----: | :---------- |
| ~~`__GL_NextGenCompiler`~~ | ~~`1` or `0`~~ | ~~Using the Vulkan SPIR-V Compiler. The goal is to reduce shader compilation time and shader system memory consumption~~ |
| `__GL_SHADER_DISK_CACHE` | `1` or `0` |  |
| `__GL_SHADER_DISK_CACHE_PATH` | `$PATH/TO/` |  |
| `__GL_SHADER_DISK_CACHE_SKIP_CLEANUP` | `1` or `0` | Remove the shader cache size limit that is 125Mb (NB: disable this limit with the value `1`) (_[Nvidia Forum](https://forums.developer.nvidia.com/t/opengl-shader-disk-cache-max-size-garbage-collection/60056)_)|
| `__GL_SHOW_GRAPHICS_OSD` | `1` or `0` | Showing the Graphics API Visual Indicator and FPS |
| `__GL_THREADED_OPTIMIZATION` | `1` or `0` | For the OpenGL games, allow the driver NVIDIA to work multi threaded. This speeds up when the drivers has a lot to do, but when your CPU is filled to the max, it can lower fps (Enable by default when the driver thinks it can improve performance) |

### Open-source driver Mesa
There is a full list of environment variables available [here](https://www.mesa3d.org/envvars.html).

| Environment Variables | Value(s) | Description |
| :------------------- | :----: | :---------- |
| `GALLIUM_HUD` | `fps` | Showing Overlay FPS |
| `RADV_PERFTEST` | `aco` | Enable by default on [Mesa 20.2](https://docs.mesa3d.org/relnotes/20.2.0.html). For the AMD GPU users, ACO is an open-source shader compiler developed by Valve. It offers lesser compilation time and also provides more FPS (_[Phoronix](https://www.phoronix.com/scan.php?page=article&item=radv-aco-llvm&num=1)_) |
| `mesa_glthread` | `true` or `false` | [Performance](https://www.gamingonlinux.com/wiki/Performance_impact_of_Mesa_glthread) and [amelioration with Mesa 20.0](https://www.phoronix.com/scan.php?page=news_item&px=Faster-Emulators-Mesa-GL-Thread) |



Tips and tricks
---------------
* **Change Windows version : `winecfg -v win10` requires Wine 5.7+**
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



Troubleshooting
---------------
* **[EXPERIMENTAL]** For the configuration of 8 Go RAM, with DXVK, he is possible that you have an error `DxvkMemoryAllocator: Memory allocation failed`. You can use this procedure ([here](https://www.reddit.com/r/linux_gaming/comments/em97io/regarding_the_dxvkmemoryallocator_memory)) but read the comments please.




Acknowledgements
----------------
* [Wine](https://winehq.org) 
* [Etienne Juvigny](https://github.com/Tk-Glitch)
* [Hans-Kristian Arntzen](https://github.com/HansKristian-Work)
* [Philip Rebohle](https://github.com/doitsujin)
* [Joshua Ashton](https://github.com/Joshua-Ashton)
* [GameHub](https://github.com/tkashkin/GameHub)
* [Lutris](https://github.com/lutris)
* [CD Projekt RED](https://en.cdprojektred.com)
* Valve [Proton](https://github.com/ValveSoftware/Proton)




Licence
-------
Available in [LICENSE](LICENSE) file<br>

**Copyright (C)** 2019-2021 Alexis Peypelut alias IroAlexis
