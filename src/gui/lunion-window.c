/* lunion-window.c
 *
 * Copyright (C) 2020 Alexis Peypelut <peypeluta@live.fr>
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

#include "lunion-window.h"


struct _LunionWindow
{
	GtkApplicationWindow parent;
	//GtkHeaderBar* headerbar;
};



G_DEFINE_TYPE (LunionWindow, lunion_window, GTK_TYPE_APPLICATION_WINDOW)



static void lunion_window_class_init (LunionWindowClass* class)
{
	/* GApplicationClass* application_class = G_APPLICATION_CLASS (class); */

	/* application_class->activate = lunion_window_activate; */

	/* gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "lunion-window.ui"); */
}

static void lunion_window_init (LunionWindow* app)
{
	/* gtk_init_template (GTK_WINDOW (app)); */
}

LunionWindow* lunion_window_new (GtkApplication* app)
{
	return g_object_new (lunion_window_get_type (),
						 "application", app,
						 "title", "Lunion",
						 "window-position", GTK_WIN_POS_CENTER,
						 NULL);
}


