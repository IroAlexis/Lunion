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
	GtkWidget*           m_menubutton;
	GtkWidget*           m_popover;
	GtkWidget*           m_menutitle;
};



G_DEFINE_TYPE (LunionWindow, lunion_window, GTK_TYPE_APPLICATION_WINDOW)

static void lunion_window_class_init (LunionWindowClass* klass)
{
}


static void lunion_window_init (LunionWindow* self)
{
	self->m_headerbar = gtk_header_bar_new ();
	self->m_menubutton = gtk_menu_button_new();
	self->m_popover = gtk_popover_new();
	self->m_menutitle = gtk_toggle_button_new_with_label("Lunion");
	gtk_popover_set_child (GTK_POPOVER (self->m_popover), self->m_menutitle);
	
	gtk_menu_button_set_direction (GTK_MENU_BUTTON (self->m_menubutton),
								   GTK_ARROW_NONE);
	gtk_menu_button_set_popover (GTK_MENU_BUTTON (self->m_menubutton),
								 self->m_popover);
	gtk_popover_set_position (GTK_POPOVER (self->m_popover),
							  GTK_POS_BOTTOM);
	
	gtk_window_set_titlebar (GTK_WINDOW (self), self->m_headerbar);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar),
							 self->m_menubutton);
	//gtk_window_set_title (GTK_WINDOW (self), "Lunion");
	
	gtk_widget_show (self->m_headerbar);
}


GtkWidget* lunion_window_new (LunionApplication* app)
{
	return g_object_new (LUNION_TYPE_WINDOW,
						 "application", app,
						 "title", "Lunion",
						 NULL);
}
