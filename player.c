/**
* @brief It implements the player functions
*
* @file player.c
* @author Paulina Kasperkiewicz
* @version 1.0
* @date 13-02-2018
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"
#include "object.h"

struct _Player {
	Id id;
	char name[WORD_SIZE + 1];
	Id player_location;
	Object* object;
};
/*Creating a new player*/
Player* player_create(Id id)
{
	Player *newPlayer = NULL;
	
	/*allocate memory for a new player*/
	newPlayer = (Player *)malloc(sizeof(Player));

	if (newPlayer == NULL)
		return NULL;

	newPlayer->id = id;
	newPlayer->name[0] = '\0';
	newPlayer->player_location = NO_ID;
	newPlayer->object = object_create(NO_ID);

	return newPlayer;
}

/*destroying the player - deallocate memory block */
STATUS player_destroy(Player* player)
{
	if (!player)
		return ERROR;

	free(player);
	player = NULL;

	return OK;
}

/*Setting the name of player*/
STATUS player_set_name(Player* player, char* name)
{
	if (!player || !name) {
		return ERROR;
	}

	if (!strcpy(player->name, name))
	{
		return ERROR;
	}

	return OK;
}

/* Setting the id of the player */
STATUS player_set_id(Player* player, Id id) 
{
	if (!player || !id) 
	{
		return ERROR;
	}

	player->id = id;

	return OK;
}
STATUS player_set_location(Player* player, Id id) 
{
	if (!player || !id) 
	{
		return ERROR;
	}

	player->player_location = id;

	return OK;
}


/* Setting the player object */
STATUS player_set_object(Player* player, Object* object)
{
	if (!player || !object)
		return ERROR;

	player->object = object;

	return OK;
}

/* Getting the id of the player */
Id player_get_id(Player* player)
{
	if (!player)
		return NO_ID;

	return player->id;
}
/* Getting the player location id*/
Id player_get_location(Player* player)
{
	if (!player)
		return NO_ID;

	return player->player_location;
}
/* Getting the name of the player */
const char * player_get_name(Player* player) 
{
	if (!player)
	{
		return NULL;
	}
	return player->name;
}
/* Getting the object in the player structure */
Object* player_get_object(Player* player)
{
	if (!player)
		return NULL;

	return player->object;
}
/* Print the name of player*/
STATUS player_print(Player* player)
{
	Id idaux = NO_ID;
	//If player doesn't exist then return error
	if (!player)
		return ERROR;
	// Assign value of id player to the variable idaux
	idaux = player_get_id(player);
	// Checking if adaux has some value
	if (NO_ID != idaux)
		fprintf(stdout, "---> Player Id: %ld.\n", idaux);
	else
		fprintf(stdout, "---> Entered player doesn't exist.\n");
	return OK;
}
