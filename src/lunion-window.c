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
//#include "lunion-headerbar.h"



struct _LunionWindow
{
	GtkApplicationWindow parent;
	GtkWidget*           m_headerbar;

	GtkWidget*           m_add;
	GMenuModel*          m_addmenu;

	GtkWidget*           m_search;
	GtkWidget*           m_box;
	GtkWidget*           m_viewtoggle;
	GtkWidget*           m_viewoption;
	GMenuModel*          m_viewmenu;

	GtkWidget*           m_appoption;
	GMenuModel*          m_appmenu;
};


enum lunion_menu_add_position
{
	LUNION_ADD_GAME,
	LUNION_ADD_TOOL,
	LUNION_ADD_PLATEFORM
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



static GMenuModel* lunion_window_build_addmenu (void)
{
	GMenu* menu = g_menu_new ();
	GMenuItem* item = NULL;

	item = g_menu_item_new("Add a new game", "app.none");
	g_menu_insert_item (menu, LUNION_ADD_GAME, item);
	g_object_unref (item);

	item = g_menu_item_new("Add a new tool", "app.none");
	g_menu_insert_item (menu, LUNION_ADD_TOOL, item);
	g_object_unref (item);

	item = g_menu_item_new("Connect a plateform", "app.none");
	g_menu_insert_item (menu, LUNION_ADD_PLATEFORM, item);
	g_object_unref (item);

	return G_MENU_MODEL (menu);
}

static GMenuModel* lunion_window_build_appmenu (void)
{
	GMenu* menu = g_menu_new ();
	GMenuItem* item = NULL;
	
	item = g_menu_item_new("Preferences", "app.none");
	g_menu_insert_item (menu, LUNION_PREFERENCES, item);
	g_object_unref (item);
	
	item = g_menu_item_new("Keyboard Shortcuts", "app.none");
	g_menu_insert_item (menu, LUNION_KEYBOARD_SHORTCUT, item);
	g_object_unref (item);
	
	item = g_menu_item_new ("About Lunion", "app.about");
	g_menu_insert_item (menu, LUNION_ABOUT, item);
	g_object_unref (item);
	
	item = g_menu_item_new ("Quit", "app.quit");
	g_menu_insert_item (menu, LUNION_QUIT, item);
	g_object_unref (item);
	
	return G_MENU_MODEL (menu);
}


static GMenuModel* lunion_window_build_viewmenu (void)
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


static void lunion_window_headerbar_start (LunionWindow* self)
{
	self->m_add = gtk_menu_button_new ();
	self->m_addmenu = lunion_window_build_addmenu ();
	gtk_menu_button_set_icon_name (GTK_MENU_BUTTON (self->m_add), "list-add-symbolic");
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_add), G_MENU_MODEL (self->m_addmenu));
}


static void lunion_window_headerbar_center (LunionWindow* self)
{
	// TODO Waiting libadwaita (libhandy)
}


static void lunion_window_headerbar_end (LunionWindow* self)
{
	self->m_search = gtk_button_new_from_icon_name ("edit-find-symbolic");
	self->m_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	self->m_viewtoggle = gtk_button_new ();
	gtk_button_set_icon_name (GTK_BUTTON (self->m_viewtoggle), "view-list-symbolic");
	self->m_viewoption = gtk_menu_button_new ();
	self->m_appoption = gtk_menu_button_new ();

	gtk_box_append (GTK_BOX (self->m_box), self->m_viewtoggle);
	gtk_box_append (GTK_BOX (self->m_box), self->m_viewoption);
	gtk_widget_add_css_class (self->m_box, "linked");
	gtk_widget_add_css_class (gtk_widget_get_first_child (self->m_viewoption), "disclosure-button");

	self->m_viewmenu = lunion_window_build_viewmenu ();
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_viewoption), G_MENU_MODEL (self->m_viewmenu));

	self->m_appmenu = lunion_window_build_appmenu ();
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_appoption), G_MENU_MODEL (self->m_appmenu));
	gtk_menu_button_set_direction (GTK_MENU_BUTTON (self->m_appoption), GTK_ARROW_NONE);
}


static void lunion_window_init (LunionWindow* self)
{
	self->m_headerbar = gtk_header_bar_new ();

	// Title
	gtk_window_set_titlebar (GTK_WINDOW (self), self->m_headerbar);

	lunion_window_headerbar_start (self);
	lunion_window_headerbar_end (self);

	// Assemble
	gtk_header_bar_pack_start (GTK_HEADER_BAR (self->m_headerbar), self->m_add);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar), self->m_appoption);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar), self->m_box);
	gtk_header_bar_pack_end (GTK_HEADER_BAR (self->m_headerbar), self->m_search);
	//gtk_window_set_title (GTK_WINDOW (self), "Lunion");

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
