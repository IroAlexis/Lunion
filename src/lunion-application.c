/* lunion-application.c
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

#include "lunion-application.h"
#include "lunion-window.h"



struct _LunionApplication
{
	GtkApplication m_parent;
	GdkDisplay*    m_display;

	GtkWidget*     m_mainwindow;
};


G_DEFINE_TYPE (LunionApplication, lunion_application, GTK_TYPE_APPLICATION)



static void lunion_application_action_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void lunion_application_action_about (GSimpleAction *action, GVariant *parameter, gpointer user_data);


static void lunion_application_startup (GApplication* app);
static void lunion_application_activate (GApplication* app);
static void lunion_application_finalize(GObject* object);
static void lunion_application_class_init (LunionApplicationClass* klass);
static void lunion_application_init (LunionApplication* self);


static GActionEntry lunion_application_actions[] =
{
	{ "quit", lunion_application_action_quit, NULL, NULL, NULL, { 0, 0, 0 } },
	{ "about", lunion_application_action_about, NULL, NULL, NULL, { 0, 0, 0 } },
};


static void lunion_application_action_about (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	LunionApplication* app = user_data;

	lunion_window_show_about (LUNION_WINDOW (gtk_application_get_active_window (GTK_APPLICATION (app))));
}


static void lunion_application_action_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	LunionApplication* self = LUNION_APPLICATION (user_data);

	gdk_display_close (self->m_display);
	g_application_quit (G_APPLICATION (self));
}


static void lunion_application_startup (GApplication* app)
{
	LunionApplication* self = LUNION_APPLICATION (app);;

	G_APPLICATION_CLASS (lunion_application_parent_class)->startup (app);

	self->m_display = gdk_display_get_default ();
	self->m_mainwindow = lunion_application_create_window (self);
}


static void lunion_application_activate (GApplication* app)
{
	LunionApplication* self = LUNION_APPLICATION (app);

	G_APPLICATION_CLASS(lunion_application_parent_class)->activate(app);

	g_action_map_add_action_entries(G_ACTION_MAP(self), lunion_application_actions, G_N_ELEMENTS(lunion_application_actions), self);

	gtk_window_present (GTK_WINDOW (self->m_mainwindow));
}


static void lunion_application_finalize(GObject* object)
{
	G_OBJECT_CLASS (lunion_application_parent_class)->finalize (object);
}


static void lunion_application_class_init (LunionApplicationClass* klass)
{
	GApplicationClass* application_class = G_APPLICATION_CLASS (klass);
	GObjectClass* object_class = G_OBJECT_CLASS (klass);

	application_class->startup = lunion_application_startup;
	application_class->activate = lunion_application_activate;

	object_class->finalize = lunion_application_finalize;
}


static void lunion_application_init (LunionApplication* self)
{
}


GtkWidget* lunion_application_create_window (LunionApplication* self)
{
	GtkWidget* mainwindow;
	GtkCssProvider* provider;
	GFile* css;

	// TODO Check error
	css = g_file_new_for_path ("src/lunion.css");

	// Load our css theme
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_file (provider, css);
	gtk_style_context_add_provider_for_display (self->m_display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	// Window
	mainwindow = lunion_window_new (self);

	g_object_unref (css);

	return mainwindow;
}


LunionApplication* lunion_application_new (void)
{
	LunionApplication* app = NULL;

	app = g_object_new (LUNION_TYPE_APPLICATION,
	                    "application-id", APPLICATION_ID,
	                    "flags", G_APPLICATION_FLAGS_NONE,
	                    NULL);

	return app;
}

