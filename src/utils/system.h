/* system.h
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

#ifndef LUNION_SYSTEM_H
#define LUNION_SYSTEM_H



typedef struct _l_data
{
	char*          str;
	struct _l_data* next;
} l_data;



/*!
 * @brief Build the game's list in a folder
 * @param path Path where is the games
 * @return List build, NULL otherwise
 */
l_data* lunion_alloc_list_gamedir (const char* path);



// LUNION_SYSTEM_H
#endif
