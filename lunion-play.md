Lunion Play
===========


Install process
---------------
* Set up the Wine prefix
```
$ WINEPREFIX=/path/to/prefix WINEARCH=win64 WINEDLLOVERRIDES="mscoree,mshtml=" WINEDEBUG=-all /path/to/wine/bin/wineboot -i

# Need to wait for files to be written to disk (ext4)
```

* Install the application
```
$ WINEPREFIX=/path/to/prefix WINEDLLOVERRIDES="winemenubuilder.exe=" WINEDEBUG=-all /path/to/wine/bin/wine /path/to/file.exe
```

* Set up DXVK and/or VKD3D-Proton
  * [DXVK](https://github.com/doitsujin/dxvk): https://github.com/doitsujin/dxvk/releases
  * [VKD3D-Proton](https://github.com/HansKristian-Work/vkd3d-proton): https://github.com/HansKristian-Work/vkd3d-proton/releases
```
$ WINEPREFIX=/path/to/prefix WINEDLLOVERRIDES="mscoree,mshtml=" PATH=/path/to/wine/bin/:$PATH /path/to/dxvk/setup_install.sh install
$ WINEPREFIX=/path/to/prefix WINEDLLOVERRIDES="mscoree,mshtml=" PATH=/path/to/wine/bin/:$PATH /path/to/vkd3d-proton/setup_install.sh install
```

* Finished, now you have to go to the application root  and launch it
```
$ cd /path/to/prefix/drive_c/path/to/application
$ WINEPREFIX=/path/to/prefix {WINEFSYNC=1 | WINEESYNC=1} /path/to/wine/bin/{wine | wine64} file.exe
```

Note : With Lunion, `prefix` it is `windata`.

