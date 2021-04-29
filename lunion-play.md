Lunion Play
===========
You can have a game list that launch with this method [here](https://github.com/IroAlexis/lunion/wiki/Tested-Windows-games-list) :frog:

Install process
---------------
* Set up the Wine prefix:
``` bash
$ WINEPREFIX=/path/to/prefix WINEARCH=win64 WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe=" WINEDEBUG=-all /path/to/wine/bin/wineboot -i && /path/to/wine/bin/wineserver --wait
```

* Install the application:
``` bash
$ WINEPREFIX=/path/to/prefix WINEDLLOVERRIDES="winemenubuilder.exe=" WINEDEBUG=-all /path/to/wine/bin/wine /path/to/file.exe
```

* (Optionnal) Set up DXVK and/or VKD3D-Proton
  * [DXVK](https://github.com/doitsujin/dxvk): https://github.com/doitsujin/dxvk/releases
  * [VKD3D-Proton](https://github.com/HansKristian-Work/vkd3d-proton): https://github.com/HansKristian-Work/vkd3d-proton/releases
``` bash
$ WINEPREFIX=/path/to/prefix WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe=" PATH=/path/to/wine/bin/:$PATH /path/to/dxvk/setup_install.sh install && /path/to/wine/bin/wineserver --wait
$ WINEPREFIX=/path/to/prefix WINEDLLOVERRIDES="mscoree,mshtml,winemenubuilder.exe=" PATH=/path/to/wine/bin/:$PATH /path/to/vkd3d-proton/setup_install.sh install && /path/to/wine/bin/wineserver --wait
```

Launch game
-----------
* Now you have to go to the game root and launch it:
``` bash
$ cd /path/to/prefix/drive_c/path/to/game
$ WINEPREFIX=/path/to/prefix {WINEFSYNC=1 | WINEESYNC=1} /path/to/wine/bin/{wine | wine64} file.exe && /path/to/wine/bin/wineserver --wait
```
