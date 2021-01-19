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



static void lunion_application_startup (GApplication* app)
{
	LunionApplication* self = LUNION_APPLICATION (app);;
	
	G_APPLICATION_CLASS (lunion_application_parent_class)->startup (app);
	
	// Window
	self->m_window = lunion_window_new (self);
}

static void lunion_application_activate (GApplication* app)
{
	LunionApplication* self = LUNION_APPLICATION (app);
	
	G_APPLICATION_CLASS(lunion_application_parent_class)->activate(app);
	
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
