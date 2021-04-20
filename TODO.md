# TODO
## Notes
* **Paths begin '/' and terminate without '/'**
* Using https://www.steamgriddb.com for game covers
* Make a specific window (GtkDialog ?) to take something other than the official cover provided by SteamGridDB
* GOG authentication WebKit window (390x500) or redirect to default browser
* Displaying a message or window advising the user to run the game's .exe and not the one from Ubisoft Connect


## In Progress
### 0.1_alpha1
* Database creation and implement basic queries
* Add a game and launch this game (just click on cover) :
  * Click on `Add a game` and select the plateform (we return a value that can be identifate the selected plateform)
  * Open a GtkDialog with GtkListBox :
    * Fill the filed `Name` (slug build automaticly)
    * Fill the field `Prefix directory` (if windows is selected)
    * Choose the file in the field `Executable`
    * The field `Working directory` is fill automaticly fom `Executable` (state : `insensitive`)
    * Fill the field `Argument(s)`


## Features
### Planned
* Display the installed runners (*and others...*) and can them uninstall easly
* Using XML for the configuration file: `.conf`
* [GOG.com] Support of DLCs installation option
* Implement a message (or something) for Ubisoft Connect games for invit the user change the default .exe

### No tested
* Multi-monitor


### GOG API
* https://gogapidocs.readthedocs.io/en/latest/auth.html#authorizing-a-request
* List user game : https://embed.gog.com/account/getFilteredProducts?mediaType=1 (use products[x].title)


## Ideas
### Launch Lunion
* Create the user specific data file
* Create or check the default configuration file in `~/.config/lunion/`


### Install game
* Download the game with the api corresponding
* Create the game folder (`$HOME/Games/slug-game`) and this subfolders (`$HOME/Games/slug-game/shaders`)
* Create the gameinfo file in `$HOME/Games/slug-game`


### Lunion Play functions
#### Runtime
Check the github api (release) for always download the DXVK (and VKD3D Proton) latest version `lunion_check_runtime_lastet_version ()`
#### Launch a game
Launch in the another thread or fork for play the game `lunion_play_launch_game ()`.

Proceed to initialize the environment variables in the new thread/fork with a function `lunion_play_init_env ()`. This function call a sub function for set a environment variable `lunion_play_set_env_var (const char* varname, const char* value)`. By default, we initialize this environment variables:
* PATH (Wine ; default : `PATH=$HOME/.local/share/lunion/tools/lunion-play/bin/:$PATH`)
* WINEDLLOVERRIDES (default : `WINEDLLOVERRIDES="winemenubuilder.exe="`)
* WINEDEBUG (default : `WINEDEBUG=-all`)
* WINEESYNC/WINEFSYNC (later WINESYNC ?)
* the DXVK variables (if DXVK is enable)
* the VKD3D Proton variables (if VKD3D Proton is enable)
