#include <gtk/gtk.h>
#include <glib-object.h>
#include <gio/gio.h>


#ifndef LUNION_APPLICATION_H
#define LUNION_APPLICATION_H

G_BEGIN_DECLS


#define LUNION_TYPE_APPLICATION (lunion_application_get_type ())
G_DECLARE_FINAL_TYPE (LunionApplication, lunion_application, LUNION, APPLICATION, GtkApplication)


LunionApplication* lunion_application_new (void);


G_END_DECLS


#endif /* _LUNION_APPLICATION_H_ */

