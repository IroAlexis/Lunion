#ifndef LUNION_WINDOW_H
#define LUNION_WINDOW_H

#include <gtk/gtk.h>
#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS



#define LUNION_TYPE_WINDOW (lunion_window_get_type ())
G_DECLARE_FINAL_TYPE (LunionWindow, lunion_window, LUNION, WINDOW, GtkApplicationWindow)



LunionWindow* lunion_window_new (GtkApplication* app);



G_END_DECLS

#endif /* _LUNNION_WINDOW_H_ */

