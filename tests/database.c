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



static void test_failure (const char* msg)
{
	fprintf (stderr, "%s", msg);
	fprintf (stderr, ANSI_COLOR_RED "FAILURE\n"  ANSI_COLOR_RESET);
}


static void test_success (const char* msg)
{
	fprintf (stderr, "%s", msg);
	fprintf (stderr, ANSI_COLOR_GREEN "SUCCESS\n"  ANSI_COLOR_RESET);
}


int test_lunion_add_game (sqlite3** db, const char* g_name)
{
	char* slug = NULL;

	slug = lunion_convert_to_unix_style (g_name);

	if (lunion_add_game (*db, g_name, slug) != EXIT_SUCCESS)
	{
		free (slug);
		test_failure ("[+] test:: lunion_add_game: ");

		return EXIT_FAILURE;
	}

	free (slug);
	test_success ("[+] test:: lunion_add_game: ");

	return EXIT_SUCCESS;
}


int test_lunion_close_database (sqlite3** db)
{
	if (lunion_close_database (db) != SQLITE_OK)
	{
		test_failure ("[+] test:: lunion_close_database: memory leak: ");
		return EXIT_FAILURE;
	}

	test_success ("[+] test:: lunion_close_database: ");
	return EXIT_SUCCESS;
}


int test_lunion_connect_database (sqlite3** db)
{
	*db = lunion_connect_database ("/tmp/test.db");
	if (NULL == *db)
	{
		test_failure ("[+] test:: lunion_connect_database: ");
		return EXIT_FAILURE;
	}

	test_success ("[+] test:: lunion_connect_database: ");
	return EXIT_SUCCESS;
}


int test_lunion_delete_game (sqlite3** db, int id)
{
	// TODO Need a comparaison function for return correctly the test state
	if (lunion_delete_game (*db, id) != EXIT_SUCCESS)
	{
		test_failure ("[+] test:: lunion_delete_game: ");
		return EXIT_FAILURE;
	}

	test_success ("[+] test:: lunion_delete_game: ");
	return EXIT_SUCCESS;
}


int test_lunion_init_database(sqlite3** db)
{
	fprintf (stderr, "[+] test:: lunion_init_database: rework the test\n");

	lunion_init_database (*db);

	return EXIT_FAILURE;
}


int main ()
{
	sqlite3* db = NULL;

	test_lunion_connect_database (&db);

	test_lunion_init_database (&db);
	test_lunion_add_game (&db, "Thronebreaker: The Witcher Tales");
	test_lunion_add_game (&db, "Horizon Zero Dawn™ Complete Edition");
	test_lunion_add_game (&db, "Assassin's Creed®: Director's Cut");
	test_lunion_delete_game (&db, 1);

	test_lunion_close_database (&db);
}
