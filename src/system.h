/* system.h
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

#ifndef LUNION_SYSTEM_H
#define LUNION_SYSTEM_H

#include <dirent.h>
#include <sys/types.h>

#define USR_DATA_DIR "/.local/share/lunion"
#define CONFIG_DIR   "/.config/lunion"
#define CACHE_DIR    "/.cache/lunion"


typedef struct _LunionList LunionList;



/*!
 * @brief Convert the game name to a name compatible with the Unix-style
 * @param text Game name
 * @return A pointer to the new game name allocated, NULL otherwise
 */
char* lunion_convert_to_unix_style (const char* text);


/*!
 * @brief Create a directory
 * @param path Path where we create the directory
 * @param d_name Name directory
 * @return EXIT_SUCCESS if you create the directory, EXIT_FAILURE otherwise
 */
int lunion_create_dir (const char* path, const char* d_name);


/*!
 * @brief Display the LunionList content
 * @param lst The list
 */
void lunion_display_list (LunionList* lst);


/*!
 * @brief Clear the LunionList content
 * @param lst The LunionList pointer to be deallocated
 */
void lunion_free_list (LunionList** lst);


/*!
 * @brief Recover only the absolute path a file
 * @param file The file path
 * @return A pointer to the absolute path allocated, NULL otherwise
 */
char* lunion_get_absolute_path (const char* file);


/*!
 * @brief Initialize the Lunion directories in the home directory
 * @return (WIP)
 */
int lunion_init_dirs ();


/*!
 * @brief Set an environement variable
 * @param name Name environement variable
 * @param value Value environement variable
 * @return EXIT_SUCCESS if we set the environement variable, EXIT_FAILURE otherwise
 */
int lunion_set_env_var (const char* name, const char* value);


/*!
 * @brief Free an environement variable
 * @param name Name environement variable
 * @return EXIT_SUCCESS if we free the environement variable, EXIT_FAILURE otherwise
 */
int lunion_unset_env_var (const char* name);



// LUNION_SYSTEM_H
#endif
