/* lunion-window.h
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

#ifndef LUNION_WINDOW_H
#define LUNION_WINDOW_H

#include <gtk/gtk.h>

#include "lunion-application.h"

G_BEGIN_DECLS



#define LUNION_TYPE_WINDOW (lunion_window_get_type ())

G_DECLARE_FINAL_TYPE (LunionWindow, lunion_window, LUNION, WINDOW, GtkApplicationWindow)



LunionWindow* lunion_window_new (LunionApplication* app);



G_END_DECLS

// LUNION_WINDOW_H_
#endif
