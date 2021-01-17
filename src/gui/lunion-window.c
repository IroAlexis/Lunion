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
//#include "lunion-headerbar.h"


struct _LunionWindow
{
	GtkApplicationWindow parent;
	
	GtkWidget*           m_headerbar;
};



G_DEFINE_TYPE (LunionWindow, lunion_window, GTK_TYPE_APPLICATION_WINDOW)

static void lunion_window_class_init (LunionWindowClass* klass)
{
	//GObjectClass* object_class = G_OBJECT_CLASS (klass)
	//GWidgetClass* widget_class = GTK_WIDGET_CLASS (klass);

	//widget_class->activate = lunion_window_activate;
	//widget_class->startup = lunion_window_startup;
}


static void lunion_window_init (LunionWindow* self)
{
	// Init GtkHeaderBar
	self->m_headerbar = gtk_header_bar_new ();
	
	// Set GtkHeaderBar
	gtk_window_set_titlebar (GTK_WINDOW (self), self->m_headerbar);
	gtk_window_set_title (GTK_WINDOW (self), "Lunion");
	
	gtk_widget_show (self->m_headerbar);
}


LunionWindow* lunion_window_new (LunionApplication* app)
{
	return g_object_new (LUNION_TYPE_WINDOW,
						 "application", app,
						 NULL);
}
