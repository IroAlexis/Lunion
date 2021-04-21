/* database.h
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

#ifndef LUNION_DATABASE_H
#define LUNION_DATABASE_H

#include <sqlite3.h>



int lunion_add_database_game (sqlite3* db, const char* name, const char* slug);


int lunion_add_database_gamesource (sqlite3* db, const char* name);


/*!
 * @brief Close the database stream
 * @param db Double pointer to the database stream
 * @return A sqlite3 error code (https://www.sqlite.org/rescode.html#result_code_meanings)
 */
int lunion_close_database (sqlite3** db);


/*!
 * @brief Open a database stream
 * @param f_name File name
 * @return A pointer to the database stream allocated, NULL otherwise
 */
sqlite3* lunion_connect_database (const char* f_name);


int lunion_init_gamesource_table (sqlite3** db);


/*!
 * @brief Initialize the database tables
 * @param db A double pointer to the database stream
 * @return EXIT_SUCCESS, EXIT_FAILURE otherwise
 */
int lunion_init_tables (sqlite3** db);


int lunion_verif_gamesource (sqlite3* db, const char* name);


#endif