/*
 * main.c
 * Copyright (C) 2020 Alexis Peypelut <peypeluta@live.fr>
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
	int                        ret;
	l_data*                    gamedir = NULL;
	l_data*                    tmp = NULL;
	g_autoptr (GtkApplication) app = NULL;

	// Detection installed games
	gamedir = lunion_alloc_list_gamedir ("/home/iroalexis/Games");
	fprintf (stdout, "::lunion:: liste des jeux detectees\n");
	for (tmp = gamedir; tmp != NULL; tmp = tmp->next)
		fprintf (stdout, " * %s\n", tmp->str);



	// Launch GTK window
	g_set_application_name ("Lunion");

	app = lunion_application_new ();
	g_application_set_default (G_APPLICATION (app));
	ret = g_application_run (G_APPLICATION (app), argc, argv);



	// Memory deallocation
	while (gamedir != NULL)
	{
		tmp = gamedir;
		gamedir = tmp->next;
		free (tmp->str);
		free (tmp);
	}

	return ret;
}

