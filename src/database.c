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
static int lunion_exec_command (sqlite3* db, const char* sql);

/*!
 * @brief Send a sql request (statement)
 * @param p_stmt A pointer to the database stream
 * @return EXIT_SUCCESS if the sql request send correctly, EXIT_FAILURE otherwise
 */
static int lunion_send_statement (sqlite3_stmt* p_stmt);

/*!
 * @brief Verif that the game source isn't already exist
 * @param name Game source name (local, gog, steam, epicgames)
 * @return EXIT_SUCCESS if the game source isn't exist, EXIT_FAILURE otherwise
 */
static int lunion_verif_gamesource (sqlite3* db, const char* name);

/*!
 * @brief Verif that the plateform isn't already exist
 * @param name Plateform name (linux or windows)
 * @return EXIT_SUCCESS if the plateform isn't exist, EXIT_FAILURE otherwise
 */
static int lunion_verif_plateform (sqlite3* db, const char* name);



static int lunion_exec_command (sqlite3* db, const char* sql)
{
	sqlite3_stmt* p_stmt = NULL;

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) != SQLITE_OK)
		fprintf (stderr, "[+] err:: lunion_add_database_game: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}


static int lunion_send_statement (sqlite3_stmt* p_stmt)
{
	int ret = 0;

	ret = sqlite3_step (p_stmt);
	if (ret != SQLITE_DONE && ret != SQLITE_ROW)
	{
		fprintf (stderr, "[+] err:: lunion_send_statement(sqlite3_step): code error (%d)\n", ret);

		sqlite3_finalize (p_stmt);
		return EXIT_FAILURE;
	}

	ret = sqlite3_finalize (p_stmt);
	if (ret != SQLITE_OK)
	{
		fprintf (stderr, "[+] err:: lunion_send_statement(sqlite3_finalize): code error (%d)\n", ret);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


static int lunion_verif_gamesource (sqlite3* db, const char* name)
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
		fprintf (stderr, "[+] err:: lunion_verif_gamesource: %s\n", sqlite3_errmsg(db));

	ret = sqlite3_step (p_stmt);
	sqlite3_finalize (p_stmt);

	if (ret == SQLITE_ROW)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


static int lunion_verif_plateform (sqlite3* db, const char* name)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;
	int ret;

	sql = "SELECT name FROM plateform WHERE name=@name;";
	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_verif_plateform: %s\n", sqlite3_errmsg(db));

	// We can't use lunion_send_statement here
	ret = sqlite3_step (p_stmt);
	sqlite3_finalize (p_stmt);

	if (ret == SQLITE_ROW)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_add_game (sqlite3* db, const char* name, const char* slug)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	if (name == NULL || slug == NULL)
		return EXIT_FAILURE;

	sql = "INSERT INTO game (name,slug) VALUES (@name, @slug);";
	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@slug");
		sqlite3_bind_text (p_stmt, tmp, slug, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_game: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}


int lunion_add_gamesource (sqlite3* db, const char* name)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	if (name == NULL)
		return EXIT_FAILURE;

	sql = "INSERT INTO gamesource (name) VALUES (@name);";
	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_gamesource: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}


int lunion_add_install (sqlite3* db, int gameId, int plateformId, int gamesourceId, const char* dir, const char* type)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	if (gameId <= 0 || plateformId <= 0 || gamesourceId <= 0 || dir == NULL || type == NULL)
		return EXIT_FAILURE;

	sql = "INSERT INTO install (gameId, plateformId, gamesourceId, dir, type) " \
	      "VALUES (@gameId, @plateformId, @gamesourceId, @dir, @type);";
	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@gameId");
		sqlite3_bind_int (p_stmt, tmp, gameId);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@plateformId");
		sqlite3_bind_int (p_stmt, tmp, plateformId);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@gamesourceId");
		sqlite3_bind_int (p_stmt, tmp, gamesourceId);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@dir");
		sqlite3_bind_text (p_stmt, tmp, dir, -1, 0);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@type");
		sqlite3_bind_text (p_stmt, tmp, type, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_install: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}


int lunion_add_plateform (sqlite3* db, const char* name)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	if (name == NULL)
		return EXIT_FAILURE;

	sql = "INSERT INTO plateform (name) VALUES (@name);";

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_plateform: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}


int lunion_add_tool (sqlite3* db, const char* name, const char* path, const char* exec, const char* version)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	if (name == NULL || path == NULL)
		return EXIT_FAILURE;

	if (version != NULL && exec != NULL)
		sql = "INSERT INTO tool (name, path, exec, version) VALUES (@name, @path, @exec, @version);";
	else if (exec != NULL && version == NULL)
		sql = "INSERT INTO tool (name, path, exec) VALUES (@name, @path, @exec);";
	else if (exec == NULL && version != NULL)
		sql = "INSERT INTO tool (name, path, version) VALUES (@name, @path, @version);";
	else
		sql = "INSERT INTO tool (name, path) VALUES (@name, @path);";

	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		sqlite3_bind_text (p_stmt, tmp, name, -1, 0);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@path");
		sqlite3_bind_text (p_stmt, tmp, path, -1, 0);

		if (exec != NULL)
		{
			tmp = sqlite3_bind_parameter_index(p_stmt, "@exec");
			sqlite3_bind_text (p_stmt, tmp, exec, -1, 0);
		}

		if (version != NULL)
		{
			tmp = sqlite3_bind_parameter_index(p_stmt, "@version");
			sqlite3_bind_text (p_stmt, tmp, version, -1, 0);
		}
	}
	else
		fprintf (stderr, "[+] err:: lunion_add_tool: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
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


int lunion_delete_game (sqlite3* db, int id)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	sql = "DELETE FROM game WHERE id=@id;";
	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@id");
		sqlite3_bind_int (p_stmt, tmp, id);
	}
	else
		fprintf (stderr, "[+] err:: lunion_delete_game: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}


int lunion_init_gamesource (sqlite3* db)
{
	// 1 local, 2 gog, 3 steam, 4 epicgames
	if (lunion_verif_gamesource (db, "local") != EXIT_FAILURE)
		if (lunion_add_gamesource (db, "local") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_gamesource (db, "gog") != EXIT_FAILURE)
		if (lunion_add_gamesource (db, "gog") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_gamesource (db, "steam") != EXIT_FAILURE)
		if (lunion_add_gamesource (db, "steam") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_gamesource (db, "epicgames") != EXIT_FAILURE)
		if (lunion_add_gamesource (db, "epicgames") == EXIT_FAILURE)
			return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


int lunion_init_plateform (sqlite3* db)
{
	// 1 linux, 2 windows
	if (lunion_verif_plateform (db, "linux") != EXIT_FAILURE)
		if (lunion_add_plateform (db, "linux") == EXIT_FAILURE)
			return EXIT_FAILURE;

	if (lunion_verif_plateform (db, "windows") != EXIT_FAILURE)
		if (lunion_add_plateform (db, "windows") == EXIT_FAILURE)
			return EXIT_FAILURE;

	return EXIT_SUCCESS;
}


void lunion_init_database (sqlite3* db)
{
	char* sql = NULL;
	int ret;

	fprintf (stdout, "[+] info:: lunion: Initializing database...\n");

	if (lunion_exec_command (db, "PRAGMA foreign_keys = ON;") == EXIT_FAILURE)
	{
		fprintf (stderr, "[!] err:: lunion_init_database: Need foreign key support (update sqlite3)\n");
		exit (EXIT_FAILURE);
	}

	sql = "CREATE TABLE game (" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name TEXT not null," \
	      "slug TEXT not null);";
	ret = sqlite3_table_column_metadata (db, NULL, "game", NULL, NULL, NULL, NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		lunion_exec_command (db, sql);

	sql = "CREATE TABLE gamesource (" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name TEXT not null);";
	ret = sqlite3_table_column_metadata (db, NULL, "gamesource", NULL, NULL, NULL, NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		lunion_exec_command (db, sql);

	sql = "CREATE TABLE plateform (" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name TEXT not null);";
	ret = sqlite3_table_column_metadata (db, NULL, "plateform", NULL, NULL, NULL, NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		lunion_exec_command (db, sql);

	sql = "CREATE TABLE tool (" \
	      "id INTEGER PRIMARY KEY not null," \
	      "name    TEXT not null," \
	      "path    TEXT not null," \
	      "exec    TEXT," \
	      "version TEXT);";
	ret = sqlite3_table_column_metadata (db, NULL, "tool", NULL, NULL, NULL, NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		lunion_exec_command (db, sql);

	sql = "CREATE TABLE install (" \
	      "id INTEGER PRIMARY KEY not null," \
	      "gameId       INTEGER not null," \
	      "plateformId  INTEGER not null," \
	      "gamesourceId INTEGER not null," \
	      "dir          TEXT not null," \
	      "type         TEXT not null," \
	      "FOREIGN KEY(gameId) REFERENCES game(id)," \
	      "FOREIGN KEY(plateformId) REFERENCES plateform(id), " \
	      "FOREIGN KEY(gamesourceId) REFERENCES gamesource(id));";
	ret = sqlite3_table_column_metadata (db, NULL, "install", NULL, NULL, NULL, NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		lunion_exec_command (db, sql);

	lunion_init_gamesource (db);
	lunion_init_plateform (db);

	fprintf (stdout, "[+] info:: lunion: Database initialization complete\n");
}


int lunion_update_game (sqlite3* db, int id, char* n_name, char* n_slug)
{
	char* sql = NULL;
	sqlite3_stmt* p_stmt = NULL;

	if (n_name != NULL && n_slug != NULL)
		sql = "UPDATE game SET name=@name, slug=@slug WHERE id=@id;";
	else if (NULL == n_slug)
		sql = "UPDATE game SET name=@name WHERE id=@id;";
	else if (NULL == n_name)
		sql = "UPDATE game SET slug=@slug WHERE id=@id;";
	else
		return EXIT_FAILURE;


	if (sqlite3_prepare_v2 (db, sql, -1, &p_stmt, 0) == SQLITE_OK)
	{
		int tmp = sqlite3_bind_parameter_index(p_stmt, "@name");
		if (tmp != 0)
			sqlite3_bind_text (p_stmt, tmp, n_name, -1, 0);

		tmp = sqlite3_bind_parameter_index(p_stmt, "@slug");
		if (tmp != 0)
			sqlite3_bind_text (p_stmt, tmp, n_slug, -1, 0);
	}
	else
		fprintf (stderr, "[+] err:: lunion_update_game: %s\n", sqlite3_errmsg(db));

	return lunion_send_statement (p_stmt);
}
