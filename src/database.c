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



static int callback (void* not_used, int argc, char** argv, char** col_name)
{
	int ix;

	for (ix = 0; ix < argc; ix++)
	{
		fprintf (stderr, "%s = %s\n", col_name[ix], argv[ix] ? argv [ix] : "NULL");
	}

	return EXIT_SUCCESS;
}

/*!
 * @brief Create a table in the database
 */
static int lunion_create_table (sqlite3* db, const char* sql)
{
	char* errmsg = NULL;

	if (sqlite3_exec (db, sql, callback, 0, &errmsg) != SQLITE_OK)
	{
		fprintf (stderr, "[+] err:: lunion_create_table: Error\n");
		sqlite3_free (errmsg);
		return EXIT_FAILURE;
	}

	free (errmsg);
	return EXIT_FAILURE;
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


// TODO Check the errors and the case where the tables already exist
// For the last, return an specific error
int lunion_init_tables (sqlite3** db)
{
	char* sql = NULL;

	sql = "CREATE TABLE game(" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name TEXT," \
	      "slug TEXT not null);";
	lunion_create_table (*db, sql);

	sql = "CREATE TABLE gamesource(" \
	      "id INTEGER PRIMARY KEY  not null," \
	      "name TEXT not null);";
	lunion_create_table (*db, sql);

	sql = "CREATE TABLE plateform(" \
	      "id INTEGER PRIMARY KEY  not null," \
	      "os TEXT not null);";
	lunion_create_table (*db, sql);

	return EXIT_FAILURE;
}
