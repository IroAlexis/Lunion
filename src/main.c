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


