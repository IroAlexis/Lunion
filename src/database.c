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


int lunion_init_tables (sqlite3* db)
{
	return EXIT_FAILURE;
}
