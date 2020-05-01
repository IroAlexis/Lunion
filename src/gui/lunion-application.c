#include "lunion-application.h"
#include "lunion-window.h"



struct _LunionApplication
{
	GtkApplication    parent;

	GtkWidget*     window;
};

G_DEFINE_TYPE (LunionApplication, lunion_application, GTK_TYPE_APPLICATION)



static void lunion_application_activate (GApplication* app)
{
	LunionApplication* this = LUNION_APPLICATION (app);

	gtk_window_present (GTK_WINDOW (this->window));
}

static void lunion_application_startup (GApplication* app)
{
	// Traduction: self -> soi
	LunionApplication* this = LUNION_APPLICATION (app);;

	/* G_APPLICATION_CLASS (lunion_application_parent_class)->startup (app); */

	if (!this)
	{
		this->window = lunion_window_new (GTK_APPLICATION (this));
	}
}

static void lunion_application_class_init (LunionApplicationClass* class)
{
	//GObjectClass*      gobj_class = G_OBJECT_CLASS (class);
	GApplicationClass* gapp_class = G_APPLICATION_CLASS (class);

	//gobj_class->constructed = constructed;
	gapp_class->activate = lunion_application_activate;
	gapp_class->startup = lunion_application_startup;
}

static void lunion_application_init (LunionApplication* app)
{

}

LunionApplication* lunion_application_new (void)
{
	                                       /* ,--> return LUNION_TYPE_APPLICATION */
	return g_object_new (lunion_application_get_type (),
	                     "application-id", "org.gtk.lunion"
	                     "flags", G_APPLICATION_FLAGS_NONE,
	                     NULL);
}




