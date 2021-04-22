/* database.c
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "database.h"
#include "system.h"



/*!
 * @brief Execute a sql command in the database
 * @param db A pointer to the database stream
 * @return EXIT_SUCCESS if the command execute correctly, EXIT_FAILURE otherwise
 */
static int lunion_exec_command (sqlite3* db, const char* sql)
{
	sqlite3_stmt* p_stmt = NULL;

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) != SQLITE_OK)
		fprintf (stderr, "[+] err:: lunion_add_database_game: %s\n", sqlite3_errmsg(db));

	sqlite3_step (p_stmt);

	if (sqlite3_finalize (p_stmt) != SQLITE_OK)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_add_database_game (sqlite3* db, const char* name, const char* slug)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	sql = "INSERT INTO game(name,slug)" \
	      "VALUES (@name, @slug);";

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@slug");
		sqlite3_bind_text (p_stmt, tmp, slug, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_database_game: %s\n", sqlite3_errmsg(db));

	sqlite3_step (p_stmt);

	if (sqlite3_finalize (p_stmt) != SQLITE_OK)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_add_database_gamesource (sqlite3* db, const char* name)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	sql = "INSERT INTO gamesource(name)" \
	      "VALUES (@name);";

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_database_gamesource: %s\n", sqlite3_errmsg(db));

	sqlite3_step (p_stmt);

	if (sqlite3_finalize (p_stmt) != SQLITE_OK)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_add_database_plateform (sqlite3* db, const char* name)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	sql = "INSERT INTO plateform(name)" \
	      "VALUES (@name);";

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_database_plateform: %s\n", sqlite3_errmsg(db));

	sqlite3_step (p_stmt);

	if (sqlite3_finalize (p_stmt) != SQLITE_OK)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_close_database (sqlite3** db)
{
	assert (db != NULL);

	return sqlite3_close (*db);
}


sqlite3* lunion_connect_database (const char* f_name)
{
	assert (f_name != NULL);

	sqlite3* db;

	if (sqlite3_open (f_name, &db) != SQLITE_OK)
	{
		fprintf (stderr, "[+] err:: lunion_connect_database: %s\n", sqlite3_errmsg(db));
		return NULL;
	}

	return db;
}


int lunion_init_gamesource_table (sqlite3** db)
{
	// 1 local, 2 gog, 3 steam, 4 epicgames
	if (lunion_verif_gamesource (*db, "local") != EXIT_FAILURE)
		if (lunion_add_database_gamesource (*db, "local") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_gamesource (*db, "gog") != EXIT_FAILURE)
		if (lunion_add_database_gamesource (*db, "gog") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_gamesource (*db, "steam") != EXIT_FAILURE)
		if (lunion_add_database_gamesource (*db, "steam") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_gamesource (*db, "epicgames") != EXIT_FAILURE)
		if (lunion_add_database_gamesource (*db, "epicgames") == EXIT_FAILURE)
			return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_init_plateform_table (sqlite3** db)
{
	// 1 linux, 2 windows
	if (lunion_add_database_plateform (*db, "linux") == EXIT_FAILURE)
		return EXIT_FAILURE;

	if (lunion_add_database_plateform (*db, "windows") == EXIT_FAILURE)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_init_database (sqlite3** db)
{
	char* sql = NULL;
	int ret = EXIT_SUCCESS;

	sql = "CREATE TABLE game(" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name TEXT not null," \
	      "slug TEXT not null);";
	if (lunion_exec_command (*db, sql) == EXIT_FAILURE)
		ret = EXIT_FAILURE;

	sql = "CREATE TABLE gamesource(" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name TEXT not null);";
	if (lunion_exec_command (*db, sql) == EXIT_FAILURE)
		ret = EXIT_FAILURE;

	sql = "CREATE TABLE plateform(" \
	      "id INTEGER PRIMARY KEY not null," \
	      "os TEXT not null);";
	if (lunion_exec_command (*db, sql) == EXIT_FAILURE)
		ret = EXIT_FAILURE;

	return ret;
}


int lunion_verif_gamesource (sqlite3* db, const char* name)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;
	int ret;

	sql = "SELECT name FROM gamesource WHERE name=@name;";

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_verif_gamesource: Failed to execute statement: %s\n", sqlite3_errmsg(db));

	ret = sqlite3_step (p_stmt);
	sqlite3_finalize (p_stmt);

	if (ret == SQLITE_ROW)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
