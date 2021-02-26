/* system.h
 *
 * Copyright (C) 2020-2021 Alexis Peypelut <peypeluta@live.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LUNION_SYSTEM_H
#define LUNION_SYSTEM_H

#include <dirent.h>
#include <sys/types.h>

#define CONFIG_DIR "/.local/share/lunion"

#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"


typedef struct _LunionList
{
	char*              slug;
	char*              path;
	struct _LunionList* next;
} LunionList;



int lunion_create_dir (const char* path,
											 const char* dirname);


int lunion_detect_file (const char* path,
												const char* dirname,
												const char* filename);


void lunion_free_list (LunionList** gamelst);


char* lunion_get_game_location ();


int lunion_init_dir ();


LunionList* lunion_list_games (const char* path,
															 DIR** stream,
															 struct dirent** sdir);


LunionList* lunion_search_install_games (const char* path);



// LUNION_SYSTEM_H
#endif
