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



/*!
 * @brief Add a game into the game table database
 * @param db A pointer to the database stream
 * @param name Game name
 * @param slug Game slug
 * @return EXIT_SUCCESS if the game is adding in the database, EXIT_FAILURE otherwise
 */
int lunion_add_game (sqlite3* db, const char* name, const char* slug);


/*!
 * @brief Add a game source into the gamesource table database
 * @param db A pointer to the database stream
 * @param name Game source name
 * @return EXIT_SUCCESS if the game source is adding in the database, EXIT_FAILURE otherwise
 */
int lunion_add_gamesource (sqlite3* db, const char* name);


/*!
 * @brief Add a plateform into the plateform table database
 * @param db A pointer to the database stream
 * @param name Plateform name
 * @return EXIT_SUCCESS if the plateform is adding in the database, EXIT_FAILURE otherwise
 */
int lunion_add_plateform (sqlite3* db, const char* name);


/*!
 * @brief Add a tool into the tool table database
 * @param db A pointer to the database stream
 * @param name Tool name
 * @param type Tool type (wine, ds,...)
 * @param path Tool path directory
 * @param exec Tool executable
 * @param version Tool version
 * @return EXIT_SUCCESS if the tool is adding in, the database, EXIT_FAILURE otherwise
 */
int lunion_add_tool (
  sqlite3* db,
  const char* name,
  const char* type,
  const char* path,
  const char* exec,
  const char* version
);


/*!
 * @brief Close the database stream
 * @param db Double pointer to the database stream
 * @return A sqlite3 error code (https://www.sqlite.org/rescode.html#result_code_meanings)
 */
int lunion_close_database (sqlite3** db);


/*!
 * @brief Delete a game in the database from his id
 * @param db A pointer to the database stream
 * @param id Id game in the database
 * @return EXIT_SUCCESS if the game is deleting in the database, EXIT_FAILURE otherwise
 */
int lunion_delete_game (sqlite3* db, int id);


/*!
 * @brief Open a database stream
 * @param f_name File name
 * @return A pointer to the database stream allocated, NULL otherwise
 */
sqlite3* lunion_connect_database (const char* f_name);


/*!
 * @brief Initialize the gamesource table
 * @param db A pointer to the database stream
 * @return EXIT_SUCCESS if the table is already initialize or
 *                      the initialization doesn't encounter any problem,
 *         EXIT_FAILURE otherwise
 */
int lunion_init_gamesource (sqlite3* db);


/*!
 * @brief Initialize the plateform table
 * @param db A pointer to the database stream
 * @return EXIT_SUCCESS if the table is already initialize or
 *                      the initialization doesn't encounter any problem,
 *         EXIT_FAILURE otherwise
 */
int lunion_init_plateform (sqlite3* db);


/*!
 * @brief Initialize the database tables
 * @param db A pointer to the database stream
 */
void lunion_init_database (sqlite3* db);


#endif
