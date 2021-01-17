#include "lunion-headerbar.h"


typedef struct
{
	GtkWidget* title;
} LunionHeaderBarPrivate;


G_DEFINE_TYPE_WITH_PRIVATE (LunionHeaderBar, lunion_header_bar, GTK_TYPE_HEADER_BAR)

static void lunion_header_bar_class_init (LunionHeaderBarClass* klass)
{
}

static void lunion_header_bar_init (LunionHeaderBar* self)
{
	LunionHeaderBarPrivate* priv = lunion_header_bar_get_instance_private (self);
	
	priv->title = gtk_label_new ("Lunion");
	
	gtk_header_bar_set_title_widget (GTK_HEADER_BAR (self), priv->title);
}

GtkWidget* lunion_header_bar_new (void)
{
	return g_object_new (LUNION_TYPE_HEADER_BAR, NULL);
}

