#include "lunion-headerbar.h"


struct _LunionHeaderBar
{
};


G_DEFINE_TYPE (LunionHeaderBar, lunion_header_bar, GTK_TYPE_HEADER_BAR)


static void lunion_header_bar_class_init (LunionHeaderBarClass* klass)
{
}

static void lunion_header_bar_init (LunionHeaderBar* self)
{
}

GtkWidget* lunion_header_bar_new (void)
{
	return g_object_new (LUNION_TYPE_HEADER_BAR, NULL);
}

