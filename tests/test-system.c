/* test-system.c
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
#include <string.h>
#include <assert.h>

#include "../src/system.h"


#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"



int test_lunion_set_env_var (const char* name, const char* value)
{
	lunion_set_env_var (name, value);

	fprintf (stderr, "[+] test:: lunion_set_env_var: ");
	if (getenv (name) == NULL)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_error_lunion_set_env_var (const char* name, const char* value)
{
	lunion_set_env_var (name, value);

	fprintf (stderr, "[+] test_err:: lunion_set_env_var: ");
	if (getenv (name) != NULL)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_lunion_get_env_var (const char* name)
{
	char* value = getenv (name);

	fprintf (stderr, "[+] test:: lunion_get_env_var: ");
	if (value == NULL)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_error_lunion_get_env_var (const char* name)
{
	char* value = getenv (name);

	fprintf (stderr, "[+] test_err:: lunion_get_env_var: ");
	if (value != NULL)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_lunion_unset_env_var (const char* name)
{
	lunion_unset_env_var (name);

	fprintf (stderr, "[+] test:: lunion_unset_env_var: ");
	if (getenv (name) != NULL)
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	return EXIT_SUCCESS;
}


int test_lunion_convert_to_unix_style (const char* text)
{
	char* t_new = NULL;

	t_new = lunion_convert_to_unix_style (text);
	if (NULL == t_new)
	{
		fprintf (stderr, "[+] test:: lunion_convert_to_unix_style: ");
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);

		free (t_new);
		return EXIT_FAILURE;
	}

	fprintf (stderr, "[+] test:: lunion_convert_to_unix_style: %s | %s\n", text, t_new);
	free (t_new);

	return EXIT_SUCCESS;
}


int test_lunion_get_absolute_path ()
{
	char* file = "/usr/bin/env";
	char* path = NULL;

	path = lunion_get_absolute_path (file);
	fprintf (stderr, "[+] test:: lunion_get_absolute_path: ");
	if (!strcmp (path, "/usr/bin/env"))
	{
		fprintf (stderr, ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
		free (path);

		return EXIT_FAILURE;
	}

	fprintf (stderr, ANSI_COLOR_GREEN "DONE\n" ANSI_COLOR_RESET);
	free (path);

	return EXIT_SUCCESS;
}


int main ()
{
	test_lunion_set_env_var ("WINEDLLOVERRIDES", "\"mscoree,mshtml,winemenubuilder.exe=\"");
	test_error_lunion_set_env_var ("WINEDEBUG=", "-all");

	test_lunion_get_env_var ("WINEDLLOVERRIDES");
	test_error_lunion_get_env_var ("WINEDEBUG=");

	test_lunion_unset_env_var ("WINEDLLOVERRIDES");

	test_lunion_convert_to_unix_style ("no_mans_sky");
	test_lunion_convert_to_unix_style ("Shadowrun: Dragonfall - Director's Cut");
	test_lunion_convert_to_unix_style ("Beyond Good & Evil™");
	test_lunion_convert_to_unix_style ("The Witcher  3     ");

	test_lunion_get_absolute_path ();
}
