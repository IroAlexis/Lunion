/* lunion-window.c
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



#include "lunion-window.h"
#include "lunion-headerbar.h"



struct _LunionWindow
{
	AdwApplicationWindow parent;
	GtkWidget*           m_box;
	GtkWidget*           m_headerbar;
};


G_DEFINE_TYPE (LunionWindow, lunion_window, ADW_TYPE_APPLICATION_WINDOW)



static void lunion_window_class_init (LunionWindowClass* klass)
{
}


static void lunion_window_init (LunionWindow* self)
{
	self->m_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	self->m_headerbar = lunion_header_bar_new ();

	// Title
	adw_application_window_set_child (ADW_APPLICATION_WINDOW (self), self->m_box);
	gtk_box_append (GTK_BOX (self->m_box), self->m_headerbar);

	gtk_widget_show (self->m_box);
	gtk_widget_show (self->m_headerbar);
}


GtkWidget* lunion_window_new (LunionApplication* app)
{
	return g_object_new (LUNION_TYPE_WINDOW,
	                     "application", app,
	                     "title", g_get_application_name(),
	                     NULL);
}

void lunion_window_show_about (LunionWindow* window)
{
	gtk_show_about_dialog (GTK_WINDOW (window),
	                       "program-name", g_get_application_name(),
	                       "version", "0.1_alpha",
	                       "copyright", "© 2020 Alexis Peypelut",
	                       "comments", "Game manager for GNOME",
	                       "license-type", GTK_LICENSE_GPL_3_0,
	                       NULL);
}
