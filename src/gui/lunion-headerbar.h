#ifndef LUNION_HEADERBAR_H
#define LUNION_HEADERBAR_H

#include <gtk/gtk.h>

G_BEGIN_DECLS


#define LUNION_TYPE_HEADER_BAR (lunion_header_bar_get_type ())

G_DECLARE_FINAL_TYPE (LunionHeaderBar, lunion_header_bar, LUNION, HEADER_BAR, GtkHeaderBar)


struct _LunionHeaderBarClass
{
	GtkHeaderBarClass* parent_class;
};


GtkWidget* lunion_header_bar_new (void);



G_END_DECLS

// LUNION_WINDOW_H_
#endif
