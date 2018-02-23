/**
* @brief It implements the game readng functions (for this iteration it only reads spaces)
*
* @file game_reader.c
* @author Paulina Kasperkiewicz
* @version 1.0
* @date 13-02-2018
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamereader.h"
#include "game.h"
#include "types.h"
#include "space.h"



/*Declaration of private functions*/
//STATUS game_load_spaces(Game* game, char* filename);
//STATUS game_add_space(Game* game, Space* space);
//Id     game_get_space_id_at(Game* game, Id Id);
//Space* game_get_space(Game* game, Id id);

/*Adding space in game*/
STATUS game_add_space(Game* game, Space* space)
{
	int i = 0;
	if (space == NULL)
	{
		return ERROR;
	}

	// execute untill not exceed value of MAX_SPACES and  the end of the space lists
	while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
	{
		i++;
	}

	// exist function when i exceeds the value of MAX_SPACES
	if (i >= MAX_SPACES)
	{
		return ERROR;
	}
	game->spaces[i] = space;

	return OK;
}
/* getting index of position in the game*/
Id game_get_space_id_at(Game* game, Id id)
{
	// Checking the correctness of data related to the item
	if (id < 0 || id >= MAX_SPACES)
	{
		return NO_ID;
	}

	return space_get_id(game->spaces[id]);
}
/*Getting list of spaces*/
Space* game_get_space(Game* game, Id id)
{
	int i = 0;

	if (id == NO_ID)
		return NULL;

	// execute untill not exceed value of MAX_SPACES and  the end of the space lists
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		if (id == space_get_id(game->spaces[i]))
			return game->spaces[i];
	}

	return NULL;
}

/*Loading game interface by using information about field connections from a file*/
STATUS game_load_spaces(Game* game, char* filename)
{
	FILE* file = NULL;
	char line[WORD_SIZE] = "";
	char name[WORD_SIZE] = "";
	char* toks = NULL;
	Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
	Space* space = NULL;
	STATUS status = OK;

	if (!filename)
		return ERROR;

	file = fopen(filename, "r");
	if (file == NULL)
		return ERROR;
	// Reading data values from a file
	while (fgets(line, WORD_SIZE, file))
	{
		/*breaks 'line+3' into a series of tokens using the delimiter "|" */
		if (strncmp("#s:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);
			toks = strtok(NULL, "|");
			strcpy(name, toks);
			toks = strtok(NULL, "|");
			north = atol(toks);
			toks = strtok(NULL, "|");
			east = atol(toks);
			toks = strtok(NULL, "|");
			south = atol(toks);
			toks = strtok(NULL, "|");
			west = atol(toks);

#ifdef DEBUG
			printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif

			space = space_create(id);
			/*If the space isn't empty, set index for all directions and add a new space*/
			if (space != NULL)
			{
				space_set_name(space, name);
				space_set_north(space, north);
				space_set_east(space, east);
				space_set_south(space, south);
				space_set_west(space, west);
				game_add_space(game, space);
			}
		}
	}

	if (ferror(file))
		status = ERROR;

	fclose(file);
	return status;
}
