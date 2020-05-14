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

	GtkWidget* header_box;
	GtkWidget* header_title;
	GtkWidget* header_sep;
	GtkWidget* header_nav;
};



G_DEFINE_TYPE (LunionWindow, lunion_window, GTK_TYPE_APPLICATION_WINDOW)



static void lunion_window_class_init (LunionWindowClass* class)
{
	//GApplicationClass* application_class = G_APPLICATION_CLASS (class);

	//application_class->activate = lunion_window_activate;
}

static void lunion_window_init (LunionWindow* self)
{
	//gtk_widget_init_template (GTK_WIDGET (self));

	self->header_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

	self->header_title = gtk_header_bar_new();
	gtk_header_bar_set_title (GTK_HEADER_BAR (self->header_title), "Lunion");
	// TODO Display if the user set the close button to left side
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (self->header_title), TRUE);

	self->header_sep = gtk_separator_new (GTK_ORIENTATION_VERTICAL);

	self->header_nav = gtk_header_bar_new ();
	//
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (self->header_nav), TRUE);

	// Assemble
	gtk_box_pack_start (GTK_BOX (self->header_box), GTK_WIDGET (self->header_title), FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (self->header_box), GTK_WIDGET (self->header_sep), FALSE, TRUE, 0);
	gtk_box_pack_end (GTK_BOX (self->header_box), GTK_WIDGET (self->header_nav), TRUE, TRUE, 0);

	// Link headerbar with window properties LunionApplication
	gtk_window_set_titlebar (GTK_WINDOW (self), self->header_box);

	gtk_window_set_decorated (GTK_WIDGET (self), TRUE);
	gtk_widget_show_all (GTK_WIDGET (self));

}

LunionWindow* lunion_window_new (GtkApplication* app)
{
	return g_object_new (lunion_window_get_type (),
						 "application", app,
						 "title", "Lunion",
						 "window-position", GTK_WIN_POS_CENTER,
						 NULL);
}
