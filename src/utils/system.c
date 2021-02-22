/* system.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "system.h"



int lunion_detect_gameinfo (const char* path, const char* gamedir)
{
	struct stat st;
	char*       tmp = NULL;
	size_t      size = strlen (path);

	tmp = strndup (path, size);

	size = strlen (tmp) + 2;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strcat (tmp, "/");

	size += strlen (gamedir) + 1;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strncat (tmp, gamedir, strlen (gamedir));

	size += strlen ("/gameinfo") + 1;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strncat (tmp, "/gameinfo", strlen ("/gameinfo"));

	//fprintf (stderr, "[-] debug:: %s\n", tmp);

	if (stat (tmp, &st) != 0)
	{
		free (tmp);
		return 1;
	}

	free (tmp);
	return 0;
}


l_data* lunion_list_games (const char* path)
{
	struct dirent* sdir = NULL;
	DIR*           stream = NULL;

	l_data* lst = NULL;
	l_data* t_ptr = NULL;
	l_data* new_data = NULL;

	stream = opendir (path);
	if (NULL == stream)
		return NULL;

	// Browse all folders
	while ((sdir = readdir (stream)) != NULL)
	{
		if (sdir->d_type == DT_UNKNOWN)
			fprintf (stderr, "[-] warn:: Your filesystems don't have full support for returning the file type in d_type\n");
		else
			if (sdir->d_type != DT_DIR)
				continue;

		// Don't save the folders "." and ".."
		// !! The instruction "continue" continue the while loop !!
		if (strcmp (sdir->d_name, ".") == 0)
			continue;

		if (strcmp (sdir->d_name, "..") == 0)
			continue;

		// Find the gameinfo file in the game directory
		if (lunion_detect_gameinfo (path, sdir->d_name) == 1)
			continue;

		new_data = (l_data*) calloc (1, sizeof (l_data));
		if (NULL == new_data)
		{
			fprintf (stderr, "[-] err:: Allocation problem\n");
			return NULL;
		}

		// Allocation for the adding of the string in the list
		new_data->str = strndup (sdir->d_name, strlen (sdir->d_name) + 1);
		if (NULL == new_data->str)
		{
			fprintf (stderr, "[-] err:: Allocation problem\n");
			return NULL;
		}

		// Link the "new_data" list with the game list
		if (lst != NULL)
		{
			t_ptr->next = new_data;
			t_ptr = t_ptr->next;
		}
		else
		{
			// Empty list
			t_ptr = new_data;
			lst = new_data;
		}
		new_data = NULL;
	}

	closedir (stream);
	t_ptr = NULL;
	stream = NULL;
	sdir = NULL;

	return lst;
}
