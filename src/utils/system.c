#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// Pas de support de Windaude
#include <sys/types.h>
#include <assert.h>

#include "system.h"



l_data* lunion_alloc_list_gamedir (const char* path)
{
	struct dirent* sdir = NULL;
	DIR*           stream = NULL;

	l_data* lst = NULL;
	l_data* t_ptr = NULL;
	l_data* new_data = NULL;

	stream = opendir (path);
	if (NULL == stream)
	{
		return NULL;
	}

	// Browse all folders
	while ((sdir = readdir (stream)) != NULL)
	{
		/* Don't display the folders "." and ".." */
		/* !! The instruction "continue" continue the while loop !! */
		if (sdir->d_name[0] == '.')
			continue;

		new_data = (l_data*) calloc(1, sizeof (l_data));
		if (NULL == new_data)
		{
			fprintf (stderr, "::lunion:: err: allocation problem\n");
			return NULL;
		}

		/* Allocation for the adding of the string in the list */
		new_data->str = strdup (sdir->d_name);
		if (NULL == new_data->str)
		{
			fprintf (stderr, "::lunion:: err: allocation problem\n");
			return NULL;
		}

		/* Link the "new_data" list with the "gamedir" list */
		if (lst != NULL)
		{
			t_ptr->next = new_data;
			t_ptr = t_ptr->next;
		}
		else
		{
			/* Empty list */
			t_ptr = new_data;
			lst = new_data;
		}

		new_data = NULL;
	}

	closedir (stream);
	stream = NULL;
	sdir = NULL;

	return lst;
}

