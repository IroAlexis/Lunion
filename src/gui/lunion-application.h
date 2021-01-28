/* lunion-application.h
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

#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>


#ifndef LUNION_APPLICATION_H
#define LUNION_APPLICATION_H

G_BEGIN_DECLS

#define APPLICATION_ID "org.gtk.lunion"

#define LUNION_TYPE_APPLICATION (lunion_application_get_type ())

G_DECLARE_FINAL_TYPE (LunionApplication, lunion_application, LUNION, APPLICATION, GtkApplication)


GtkWidget*         lunion_application_create_window (LunionApplication* self);

LunionApplication* lunion_application_new           (void);

G_END_DECLS


// _LUNION_APPLICATION_H_
#endif
