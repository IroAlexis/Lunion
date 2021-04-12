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
#include "lunion-application.h"



int main (int argc, char** argv)
{
	int                status;
	LunionApplication* app = NULL;

	if (lunion_init_dirs () != EXIT_SUCCESS)
		return EXIT_FAILURE;

	g_set_application_name ("Lunion");
	fprintf (stdout, "[+] %s\n", g_get_application_name());

	// Application
	app = lunion_application_new ();

	g_application_set_default (G_APPLICATION (app));
	status = g_application_run (G_APPLICATION (app), argc, argv);

	// Memory deallocation
	g_object_unref (app);

	return status;
}
