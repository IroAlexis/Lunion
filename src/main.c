/*
 * main.c
 * Copyright (C) 2020-2021 Alexis Peypelut <peypeluta@live.fr>
 *
 * lunion is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lunion is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>

#include "utils/system.h"
#include "gui/lunion-application.h"



int main (int argc, char** argv)
{
	int                status;
	char*              usr_path = NULL;
	LunionList*        gamelst = NULL;
	LunionList*        tmp = NULL;
	LunionApplication* app = NULL;

	lunion_init_dirs ();
	// TODO Search the conf file

	// Detection installed games
	gamelst = lunion_search_install_games ("/home/iroalexis/Games");

	// TODO Create a list display function
	fprintf (stdout, "[-] info:: List of installed games\n");
	for (tmp = gamelst; tmp != NULL; tmp = tmp->next)
		fprintf (stdout, "   > %s '%s'\n", tmp->slug, tmp->path);

	g_set_application_name ("Lunion");

	// Application
	app = lunion_application_new ();

	g_application_set_default (G_APPLICATION (app));
	status = g_application_run (G_APPLICATION (app), argc, argv);

	// Memory deallocation
	g_object_unref (app);
	lunion_free_list (&gamelst);
	free (usr_path);

	return status;
}
