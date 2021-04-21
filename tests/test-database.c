/* test-database.c
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

#include "../src/database.h"
#include "../src/system.h"


#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"



int test_lunion_close_database (sqlite3** db)
{
	fprintf (stderr, "[+] test:: lunion_close_database: ");
	if (lunion_close_database (db) != SQLITE_OK)
	{
		fprintf (stderr, "memory leak: \n");
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_lunion_connect_database (sqlite3** db)
{
	*db = lunion_connect_database ("/tmp/test.db");

	fprintf (stderr, "[+] test:: lunion_connect_database: ");
	if (NULL == *db)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_lunion_init_tables(sqlite3** db)
{
	int ret;

	ret = lunion_init_tables (db);

	fprintf (stderr, "[+] test:: lunion_init_tables: ");
	if (ret != EXIT_SUCCESS)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int main ()
{
	sqlite3* db = NULL;

	test_lunion_connect_database (&db);

	test_lunion_init_tables (&db);

	test_lunion_close_database (&db);
}
