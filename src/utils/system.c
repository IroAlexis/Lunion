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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "system.h"



int lunion_alloc_member (const char* dir, const char* path, LunionList** lst)
{
	LunionList* t_ptr = NULL;
	LunionList* new_data = NULL;

	new_data = (LunionList*) calloc (1, sizeof (LunionList));
	if (NULL == new_data)
	{
		fprintf (stderr, "[-] err:: Allocation problem\n");
		return EXIT_FAILURE;
	}

	// Allocation for the adding of the string in the list
	new_data->slug = strndup (dir, strlen (dir));
	if (NULL == new_data->slug)
	{
		fprintf (stderr, "[-] err:: Allocation problem\n");
		return EXIT_FAILURE;
	}

	new_data->path = strndup (path, strlen (path));
	if (NULL == new_data->path)
	{
		fprintf (stderr, "[-] err:: Allocation problem\n");
		return EXIT_FAILURE;
	}

	// Link the "new_data" list with the game list
	if (*lst == NULL)
		*lst = new_data;
	else
	{
		t_ptr = *lst;
		while (t_ptr->next != NULL)
			t_ptr = t_ptr->next;

		t_ptr->next = new_data;
	}

	t_ptr = NULL;
	new_data = NULL;

	return EXIT_SUCCESS;
}


int lunion_create_dir_alt (const char* path)
{
	errno = 0;

	if (mkdir (path, 0755) != 0 && errno != EEXIST)
	{
		fprintf (stderr, "[-] err:: %s", path);
		perror (": ");
		return EXIT_FAILURE;
	}

	sync ();
	return EXIT_SUCCESS;
}


int lunion_create_dir (const char* path, const char* dirname)
{
	char* tmp = NULL;
	struct stat st = {0};

	if (stat (path, &st) == -1)
		return EXIT_FAILURE;

	// Create tools directory .local/share/lunion/tools
	tmp = strndup (path, strlen (path));
	if (NULL == tmp)
	{
		fprintf (stderr, "[-] err:: Allocation problem\n");

		free (tmp);
		return EXIT_FAILURE;
	}

	tmp = (char*) realloc (tmp, (strlen (tmp) + strlen (dirname) + 1) * sizeof (char));
	strncat (tmp, dirname, strlen (dirname));
	if (lunion_create_dir_alt (tmp) == EXIT_FAILURE)
	{
		free (tmp);
		return EXIT_FAILURE;
	}

	free (tmp);
	return EXIT_SUCCESS;
}


int lunion_detect_file (const char* path, const char* dirname, const char* filename)
{
	struct stat st;
	char*       tmp = NULL;
	size_t      size = strlen (path);

	tmp = strndup (path, size);

	size = strlen (tmp) + 2;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strcat (tmp, "/");

	size += strlen (dirname) + 1;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strncat (tmp, dirname, strlen (dirname));

	size += 2;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strcat (tmp, "/");
	fprintf (stderr, "[-] info:: Search '%s' in '%s' : ", filename, tmp);

	size += strlen (filename) + 1;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strncat (tmp, filename, strlen (filename));

	if (stat (tmp, &st) != 0)
	{
		fprintf (stderr, ANSI_COLOR_RED "NO\n" ANSI_COLOR_RESET);
		free (tmp);
		return 1;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "OK\n" ANSI_COLOR_RESET);
	free (tmp);
	return 0;
}


void lunion_free_list (LunionList** gamelst)
{
	LunionList* tmp;

	while (*gamelst != NULL)
	{
		tmp = *gamelst;
		*gamelst = tmp->next;
		free (tmp->slug);
		free (tmp->path);
		free (tmp);
	}

	tmp = NULL;
	*gamelst = NULL;
}


/* TODO Work In Progress
char* lunion_get_game_location ()
{
	return NULL;
}
*/


int lunion_init_dir ()
{
	char* home = NULL;
	char* usrdata_path = NULL;

	home = getenv ("HOME");
	if (NULL == home)
	{
		fprintf (stderr, "[-] err:: User path not found\n");
		return EXIT_FAILURE;
	}

	// Copy $HOME for manipulate
	usrdata_path = (char*) calloc (strlen (home) + 1, sizeof (char));
	if (NULL == usrdata_path)
	{
		fprintf (stderr, "[-] err:: Allocation problem\n");
		return EXIT_FAILURE;
	}
	strncpy (usrdata_path, home, strlen (home));

	// Create user data directory .local/share/lunion
	lunion_create_dir (usrdata_path, USR_DATA_DIR);

	usrdata_path = (char*) realloc (usrdata_path, (strlen (usrdata_path) + strlen (USR_DATA_DIR) + 1) * sizeof (char));
	strncat (usrdata_path, USR_DATA_DIR, strlen (USR_DATA_DIR));

	lunion_create_dir (usrdata_path, "/tools");
	lunion_create_dir (usrdata_path, "/runtime");
	lunion_create_dir (usrdata_path, "/logs");

	free (usrdata_path);
	return EXIT_SUCCESS;
}


LunionList* lunion_list_games (const char* path, DIR** stream, struct dirent** sdir)
{
	DIR*           p_stream;
	struct dirent* p_sdir;

	LunionList* lst = NULL;

	p_stream = *stream;
	p_sdir = *sdir;

	// Browse all folders
	while (p_sdir != NULL)
	{
		//fprintf (stderr, "[-] debug:: %s\n", p_sdir->d_name);

		if (p_sdir->d_type != DT_DIR ||
			 strcmp (p_sdir->d_name, ".") == 0 ||
			 strcmp (p_sdir->d_name, "..") == 0 ||
			 lunion_detect_file (path, p_sdir->d_name, "gameinfo") == 1)
		{
			p_sdir = readdir (p_stream);
			continue;
		}

		lunion_alloc_member (p_sdir->d_name, path, &lst);
		p_sdir = readdir (p_stream);
	}

	p_stream = NULL;
	p_sdir = NULL;

	return lst;
}


LunionList* lunion_search_install_games (const char* path)
{
	DIR*           stream = NULL;
	struct dirent* sdir = NULL;
	LunionList* lst = NULL;

	stream = opendir (path);
	if (NULL == stream)
		return NULL;

	sdir = readdir (stream);
	if (sdir->d_type == DT_UNKNOWN)
		fprintf (stderr, "[-] info:: Filesystem don't have full support for returning the file type\n");
	lst = lunion_list_games (path, &stream, &sdir);

	closedir (stream);
	stream = NULL;
	sdir = NULL;

	return lst;
}

