/* lunion-application.c
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

#include "lunion-application.h"
#include "lunion-window.h"



struct _LunionApplication
{
	GtkApplication m_parent;
	
	GtkWidget*     m_window;
};


G_DEFINE_TYPE (LunionApplication, lunion_application, GTK_TYPE_APPLICATION)



static void lunion_application_quit (GSimpleAction *action,
									 GVariant *parameter,
									 gpointer user_data);

static void lunion_application_startup (GApplication* app);

static void lunion_application_activate (GApplication* app);

static void lunion_application_finalize(GObject* object);

static void lunion_application_class_init (LunionApplicationClass* klass);

static void lunion_application_init (LunionApplication* self);


static GActionEntry lunion_application_actions[] = {
	//{"mpc-playback-shuffle", lunion_application_playback_shuffle, NULL, "false", lunion_application_playback_change, {0, 0, 0}},
	{"quit", lunion_application_quit, NULL, NULL, NULL, {0, 0, 0}},
	{"selection-change", NULL, "i", NULL, NULL, {0, 0, 0}},
	{"selection-mode-all", NULL, NULL, NULL, NULL, {0, 0, 0}},
	{"selection-mode-none", NULL, NULL, NULL, NULL, {0, 0, 0}},
	{"selection-mode-off", NULL, NULL, NULL, NULL, {0, 0, 0}},
	{"selection-mode-on", NULL, NULL, NULL, NULL, {0, 0, 0}},
	{"selection-remove", NULL, NULL, NULL, NULL, {0, 0, 0}}
};

GtkWidget* lunion_application_create_window (LunionApplication* self,
											 GdkDisplay*        display)
{
	GtkWidget* window;
	GtkCssProvider* provider;
	GFile* css;
	
	// Check error
	css = g_file_new_for_path ("src/gui/test.css");
	
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_file (provider, css);
	gtk_style_context_add_provider_for_display (display,
												GTK_STYLE_PROVIDER (provider),
												GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	
	window = lunion_window_new (self);
	
	g_object_unref (css);
	
	return window;
}


static void lunion_application_quit (GSimpleAction *action,
									 GVariant *parameter,
									 gpointer user_data)
{
	g_application_quit (G_APPLICATION (user_data));
}

static void lunion_application_startup (GApplication* app)
{
	LunionApplication* self = LUNION_APPLICATION (app);;
	
	G_APPLICATION_CLASS (lunion_application_parent_class)->startup (app);
	
	self->m_window = lunion_application_create_window (self,
													   gdk_display_get_default ());
}

static void lunion_application_activate (GApplication* app)
{
	LunionApplication* self = LUNION_APPLICATION (app);
	
	G_APPLICATION_CLASS(lunion_application_parent_class)->activate(app);
	
	g_action_map_add_action_entries(G_ACTION_MAP(self),
									lunion_application_actions,
									G_N_ELEMENTS(lunion_application_actions),
									self);
	
	gtk_window_present (GTK_WINDOW (self->m_window));
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

LunionApplication* lunion_application_new (void)
{
	LunionApplication* app = NULL;
	
	g_set_application_name ("Lunion");
	
	app = g_object_new (LUNION_TYPE_APPLICATION,
						   "application-id", APPLICATION_ID,
						   "flags", G_APPLICATION_FLAGS_NONE,
						   NULL);
	return app;
}
