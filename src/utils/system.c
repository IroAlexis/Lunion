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
#include <sys/stat.h>

#include "system.h"



int lunion_alloc_ldata (const char* dir, const char* path, l_data** lst)
{
	l_data* t_ptr = NULL;
	l_data* new_data = NULL;

	new_data = (l_data*) calloc (1, sizeof (l_data));
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


int lunion_detect_file (const char* file, const char* path, const char* dir)
{
	struct stat st;
	char*       tmp = NULL;
	size_t      size = strlen (path);

	tmp = strndup (path, size);

	size = strlen (tmp) + 2;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strcat (tmp, "/");

	size += strlen (dir) + 1;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strncat (tmp, dir, strlen (dir));

	size += 2;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strcat (tmp, "/");
	fprintf (stderr, "[-] info:: Search '%s' in '%s' : ", file, tmp);

	size += strlen (file) + 1;
	tmp = (char*) realloc (tmp, size * sizeof (char));
	strncat (tmp, file, strlen (file));

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


void lunion_free_list (l_data** gamelst)
{
	l_data* tmp;

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


l_data* lunion_list_games (const char* path, DIR** stream, struct dirent** sdir)
{
	DIR*           p_stream;
	struct dirent* p_sdir;

	l_data* lst = NULL;

	p_stream = *stream;
	p_sdir = *sdir;

	// Browse all folders
	while (p_sdir != NULL)
	{
		//fprintf (stderr, "[-] debug:: %s\n", p_sdir->d_name);

		if (p_sdir->d_type != DT_DIR ||
			 strcmp (p_sdir->d_name, ".") == 0 ||
			 strcmp (p_sdir->d_name, "..") == 0 ||
			 lunion_detect_file ("gameinfo", path, p_sdir->d_name) == 1)
		{
			p_sdir = readdir (p_stream);
			continue;
		}

		lunion_alloc_ldata (p_sdir->d_name, path, &lst);
		p_sdir = readdir (p_stream);
	}

	p_stream = NULL;
	p_sdir = NULL;

	return lst;
}


l_data* lunion_search_install_games (const char* path)
{
	DIR*           stream = NULL;
	struct dirent* sdir = NULL;
	l_data* lst = NULL;

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

