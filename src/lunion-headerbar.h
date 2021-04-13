/* lunion-headerbar.h
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

#ifndef LUNION_HEADERBAR_H
#define LUNION_HEADERBAR_H

#include <gtk/gtk.h>

G_BEGIN_DECLS


#define LUNION_TYPE_HEADER_BAR (lunion_header_bar_get_type ())

G_DECLARE_FINAL_TYPE (LunionHeaderBar, lunion_header_bar, LUNION, HEADER_BAR, AdwBin)



GtkWidget* lunion_header_bar_new (void);



G_END_DECLS

// LUNION_WINDOW_H_
#endif
