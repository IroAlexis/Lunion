#ifndef LUNION_SYSTEM_H
#define LUNION_SYSTEM_H



typedef struct _l_data
{
	char*          str;
	struct _l_data* next;
} l_data;



/*!
 * @brief Build the game's list in a folder
 * @param path Path where is the games
 * @return List build, NULL otherwise
 */
l_data* lunion_alloc_list_gamedir (const char* path);



#endif

