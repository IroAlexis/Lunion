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
	
	GtkWidget*           m_addbutton;
	
	GtkWidget*           m_searchbutton;
	
	GtkWidget*           m_optionbox;
	GtkWidget*           m_viewbutton;
	GtkWidget*           m_menuviewbutton;
	GMenuModel*          m_menuview;
	
	GtkWidget*           m_menubutton;
	GMenuModel*          m_menu;
};


enum lunion_menu_position
{
	LUNION_PREFERENCES,
	LUNION_KEYBOARD_SHORTCUT,
	LUNION_ABOUT,
	LUNION_QUIT
};


enum lunion_menu_view_position
{
	LUNION_DOWNLOAD_COVER,
	LUNION_INSTALLED_CHECK,
	LUNION_HIDDEN_CHECK
};


G_DEFINE_TYPE (LunionWindow, lunion_window, GTK_TYPE_APPLICATION_WINDOW)



GMenuModel* lunion_window_build_menu (void)
{
	GMenu* menu = g_menu_new ();
	GMenuItem* item = NULL;
	
	item = g_menu_item_new("Preferences", "app.none");
	g_menu_insert_item (menu, LUNION_PREFERENCES, item);
	g_object_unref (item);
	
	item = g_menu_item_new("Keyboard Shortcuts", "app.none");
	g_menu_insert_item (menu, LUNION_KEYBOARD_SHORTCUT, item);
	g_object_unref (item);
	
	item = g_menu_item_new ("About Lunion", "app.quit");
	g_menu_insert_item (menu, LUNION_ABOUT, item);
	g_object_unref (item);
	
	item = g_menu_item_new ("Quit", "app.quit");
	g_menu_insert_item (menu, LUNION_QUIT, item);
	g_object_unref (item);
	
	return G_MENU_MODEL (menu);
}


GMenuModel* lunion_window_build_menu_view (void)
{
	GMenu* menu = g_menu_new ();
	GMenuItem* item = NULL;
	
	item = g_menu_item_new("Download game covers", "app.none");
	g_menu_insert_item (menu, LUNION_DOWNLOAD_COVER, item);
	g_object_unref (item);
	
	item = g_menu_item_new("Installed games", "app.none");
	g_menu_insert_item (menu, LUNION_INSTALLED_CHECK, item);
	g_object_unref (item);
	
	item = g_menu_item_new("Hidden games", "app.none");
	g_menu_insert_item (menu, LUNION_HIDDEN_CHECK, item);
	g_object_unref (item);
	
	return G_MENU_MODEL (menu);
}


static void lunion_window_class_init (LunionWindowClass* klass)
{
}


static void lunion_window_init (LunionWindow* self)
{
	self->m_headerbar = gtk_header_bar_new ();
	self->m_addbutton = gtk_button_new_from_icon_name ("list-add-symbolic");
	self->m_searchbutton = gtk_button_new_from_icon_name ("edit-find-symbolic");
	self->m_optionbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	self->m_viewbutton = gtk_button_new_from_icon_name ("view-list-symbolic");
	self->m_menuviewbutton = gtk_menu_button_new ();
	self->m_menubutton = gtk_menu_button_new ();
	
	// Title
	gtk_window_set_titlebar (GTK_WINDOW (self), self->m_headerbar);
	
	// Assemble option box
	gtk_box_append (GTK_BOX (self->m_optionbox), self->m_viewbutton);
	gtk_box_append (GTK_BOX (self->m_optionbox), self->m_menuviewbutton);
	gtk_widget_add_css_class (self->m_optionbox, "linked");
	
	// Build menu menuview
	self->m_menuview = lunion_window_build_menu_view ();
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_menuviewbutton),
									G_MENU_MODEL (self->m_menuview));
	
	// Build menu menubutton
	self->m_menu = lunion_window_build_menu ();
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_menubutton),
									G_MENU_MODEL (self->m_menu));
	gtk_menu_button_set_direction (GTK_MENU_BUTTON (self->m_menubutton),
								   GTK_ARROW_NONE);
	
	// Assemble
	gtk_header_bar_pack_start (GTK_HEADER_BAR (self->m_headerbar),
							   self->m_addbutton);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar),
							 self->m_menubutton);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar),
							 self->m_optionbox);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar),
							 self->m_searchbutton);
	//gtk_window_set_title (GTK_WINDOW (self), "Lunion");
	
	// Draw
	gtk_widget_show (self->m_headerbar);
}


GtkWidget* lunion_window_new (LunionApplication* app)
{
	return g_object_new (LUNION_TYPE_WINDOW,
						 "application", app,
						 "title", "Lunion",
						 NULL);
}
