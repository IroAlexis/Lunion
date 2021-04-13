/* lunion-headerbar.c
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

#include <adwaita.h>

#include "lunion-headerbar.h"


struct _LunionHeaderBar
{
	AdwBin parent;

	GtkWidget* m_headerbar;
	GtkWidget* m_add;

	GtkWidget* m_search;
	GtkWidget* m_box;
	GtkWidget* m_viewgrid;
	GtkWidget* m_viewlist;
	GtkWidget* m_viewoption;

	GtkWidget* m_appoption;
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


G_DEFINE_TYPE (LunionHeaderBar, lunion_header_bar, ADW_TYPE_BIN)


static GMenuModel* lunion_header_bar_build_addmenu (void)
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

static GMenuModel* lunion_header_bar_build_appmenu (void)
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


static GMenuModel* lunion_header_bar_build_viewmenu (void)
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


static void lunion_header_bar_class_init (LunionHeaderBarClass* klass)
{
}

static void lunion_header_bar_init (LunionHeaderBar* self)
{
	self->m_headerbar = adw_header_bar_new ();

	// Pack Start
	self->m_add = gtk_menu_button_new ();

	// Pack End
	self->m_search = gtk_button_new_from_icon_name ("edit-find-symbolic");
	self->m_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	self->m_viewgrid = gtk_button_new_from_icon_name ("view-grid-symbolic");
	self->m_viewlist = gtk_button_new_from_icon_name ("view-list-symbolic");
	self->m_viewoption = gtk_menu_button_new ();
	self->m_appoption = gtk_menu_button_new ();

	// Append to the headerbar
	adw_bin_set_child (ADW_BIN (self), self->m_headerbar);
	adw_header_bar_pack_start (ADW_HEADER_BAR (self->m_headerbar), self->m_add);
	adw_header_bar_pack_end (ADW_HEADER_BAR (self->m_headerbar), self->m_appoption);
	adw_header_bar_pack_end (ADW_HEADER_BAR (self->m_headerbar), self->m_box);
	adw_header_bar_pack_end (ADW_HEADER_BAR (self->m_headerbar), self->m_search);

	// Define the widgets
	gtk_menu_button_set_icon_name (GTK_MENU_BUTTON (self->m_add), "list-add-symbolic");
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_add), lunion_header_bar_build_addmenu ());

	gtk_box_append (GTK_BOX (self->m_box), self->m_viewgrid);
	gtk_box_append (GTK_BOX (self->m_box), self->m_viewlist);
	gtk_box_append (GTK_BOX (self->m_box), self->m_viewoption);
	gtk_widget_add_css_class (self->m_box, "linked");
	gtk_widget_add_css_class (gtk_widget_get_first_child (self->m_viewoption), "disclosure-button");

	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_viewoption), lunion_header_bar_build_viewmenu ());

	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (self->m_appoption), lunion_header_bar_build_appmenu ());
	gtk_menu_button_set_direction (GTK_MENU_BUTTON (self->m_appoption), GTK_ARROW_NONE);

	gtk_widget_show (self->m_headerbar);
	gtk_widget_show (self->m_add);
	gtk_widget_show (self->m_search);
	gtk_widget_show (self->m_box);
	gtk_widget_hide (self->m_viewgrid);
	gtk_widget_show (self->m_viewlist);
	gtk_widget_show (self->m_viewoption);
	gtk_widget_show (self->m_appoption);
}

GtkWidget* lunion_header_bar_new (void)
{
	return g_object_new (LUNION_TYPE_HEADER_BAR, NULL);
}

