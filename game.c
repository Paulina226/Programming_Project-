/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "gamereader.h"
#include "player.h"
#include "object.h"
#include "set.h"
#include "dice.h"

#define N_CALLBACK 7

 /**
	Define the function type for the callbacks
 */
 
 /*Paulina to Adrian: In my opinion it should be removed*/
//typedef void(*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_right(Game* game, Id id);
void game_callback_left(Game* game, Id id);
void game_callback_graps(Game* game, Id id);
void game_callback_drop(Game* game);
void game_callback_roll_the_dice(Game* game);

/*Paulina to Adiran: it should be also removed */
/*static callback_fn game_callback_fn_list[N_CALLBACK] = {
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous,
  game_callback_pick_up,
  game_callback_put_in_place,
  game_callback_roll_the_dice
}; */

/**
   Private functions
*/

STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id);

/**
   Game interface implementation
*/
/*Game interface implementation*/
STATUS game_create(Game* game)
{
	int i;

	for (i = 0; i < MAX_SPACES; i++)
	{
		game->spaces[i] = NULL;
	}
	/*Paulina to Adrian: If it deosn't work, it should be changed to 1*/
	game->player = player_create(NO_ID);
	for (i = 0; i < max_o; i++)
	{
		game->object[i] = NULL;
	}	
	game->last_cmd = NO_CMD;

  	game->dice = dice_create();

	return OK;
}

/*Creating a game based on data from files */
STATUS game_create_from_file(Game* game, char* filename)
{
	if (game_create(game) == ERROR)
		return ERROR;

	if (game_load_spaces(game, filename) == ERROR)
		return ERROR;

	game_set_player_location(game, game_get_space_id_at(game, 0));
	game_set_object_location(game, game_get_space_id_at(game, 0));

	return OK;
}
/*Destroying the game space*/
STATUS game_destroy(Game* game)
{
	int i = 0;

	for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
	{
		space_destroy(game->spaces[i]);
	}

  player_destroy(game->player);

  dice_destroy(game->dice);

  for (i = 0; (i < max_o) && (game->object[i] != NULL); i++)
	{
		object_destroy(game->object[i]);
	}

  free(game);

	return OK;
}
/*Setting player location*/
STATUS game_set_player_location(Game* game, Id id)
{
	if (id == NO_ID) {
		return ERROR;
	}

	player_set_location(game->player, id);
	return OK;
}
/*Setting object localization*/
STATUS game_set_object_location(Game* game, Id id)
{
	int i = 0;

	if (id == NO_ID)
	{
		return ERROR;
	}

	for(i=0;i<(MAX_SPACES+1);i++){
		if (space_get_id(game->spaces[i]) == id)
		{
			add_value(game->object, id);
			space_set_object(game->spaces[i],object_create(id));
		}
	}

	return OK;
}
/*Getting player localisation*/
Id game_get_player_location(Game* game)
{
	return player_get_location(game->player);
}
Object* object_get_by_id(Game* game, Id id)
{
	
	int i;
	for(i=0; i<max; i++)
	{
		if(object_get_id(game->object[i]) == id)
			return game->object[i];
			
	}
	return NULL;
}


/*Getting object localization*/
Id game_get_object_location(Game* game, Id id)
{
	int i,j;
  Set* set=NULL;

	for (i = 0;i<(MAX_SPACES+1);i++)
	{

/* I changed it and i added ner function in space and set*/
		if(space_get_object(game->spaces[i], Id)==id)
		{
			/* I don't what's going on here but in this place is error*/
      			for (j=0;j<set_get_number((Set*) space_get_set(game->spaces[i]));j++)
			{
				/*Next error*/
        			set = space_get_set(spaces[i]);
				/*Next error*/
        			if (!set_get_ids(set[j],id))
				{
          				return space_get_id(game->spaces[i]);
       			 	}
      			}
		}
	}

	return NO_ID;
}
/*Updating game after executing commands */
STATUS game_update(Game* game, T_Command cmd)
{
	game->last_cmd = cmd;
	/*Paulina to Adrian: It should be removed*/
	//(*game_callback_fn_list[cmd])(game);
	return OK;
}
/*Getting the last command which was executed*/
T_Command game_get_last_command(Game* game)
{
	return game->last_cmd;
}
/*Printing the game and showing the position of the object and player */
void game_print_data(Game* game)
{
	int i = 0;

	printf("\n\n-------------\n\n");

	printf("=> Spaces: \n");
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		space_print(game->spaces[i]);
	}

	printf("=> Object location: %d\n", (int)game_get_object_location(game));
	printf("=> Player location: %d\n", (int)player_get_location(game->player));
  //??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	printf("prompt:> ");
}
/*Checking if the game is over*/
BOOL game_is_over(Game* game)
{
	return FALSE;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game* game) {}

void game_callback_exit(Game* game) {}
/*Moving one step forward*/
void game_callback_following(Game* game)
{
	int i = 0;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	//player location is assigned to a variable "space_id"
	space_id = game_get_player_location(game);
	//If the "space_id" still equals to "NO_ID", exit
	if (space_id == NO_ID)
	{
		return;
	}
	//Execute a loop until "i" exceeds the value of the determined maximum size of space or the end of the list of created spaces
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		current_id = space_get_id(game->spaces[i]);
		//Comparing whether the field is the one on which the player is standing
		if (current_id == space_id)
		{
			//Assign a value from the south of this field (one more than the current one)
			current_id = space_get_south(game->spaces[i]);
			if (current_id != NO_ID)
			{
				//Setting a new localization for the player
				game_set_player_location(game, current_id);
			}
			return;
		}
	}
}
/* Return to the previous position*/
void game_callback_previous(Game* game)
{
	int i = 0;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	//player location is assigned to a variable "space_id"
	space_id = game_get_player_location(game);
	//If the "space_id" still equals to "NO_ID", exit
	if (NO_ID == space_id)
	{
		return;
	}
	//Execute a loop until "i" exceeds the value of the determined maximum size of space or the end of the list of created spaces
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		current_id = space_get_id(game->spaces[i]);
		//Comparing whether the field is the one on which the player is standing
		if (current_id == space_id)
		{
			//ssign a value from the north of this field (one less than the current one)
			current_id = space_get_north(game->spaces[i]);
			if (current_id != NO_ID)
			{
				//Setting a new localization for the player
				game_set_player_location(game, current_id);
			}
			return;
		}
	}
}
void game_callback_graps(Game* game, Id object) {
	int i ;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	//player location is assigned to a variable "space_id"
	space_id = game_get_player_location(game);
	//If the "space_id" still equals to "NO_ID", exit
	if (NO_ID == space_id)
	{
		return;
	}
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		current_id = space_get_id(game->spaces[i]);
		//Comparing whether the field is the one on which the player is standing
		if (current_id == space_id)
		{
			if (!set_get_ids(game->spaces[i]->object, object))
				return;
			if (player_get_object(game->player) == NO_ID)
			{
				player_set_object(game->player, object);

				space_remove_object(game->spaces[i], object_get_by_id(object));
			}
			return;
		}
	}

}

void game_callback_drop(Game* game) {
	int i = 0; 
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	//player location is assigned to a variable "space_id"
	space_id = game_get_player_location(game);
	//If the "space_id" still equals to "NO_ID", exit
	if (NO_ID == space_id)
	{
		return;
	}
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		current_id = space_get_id(game->spaces[i]);
		//Comparing whether the field is the one on which the player is standing
		if (current_id == space_id)
		{

			if (player_get_object(game->player) != NO_ID)
			{
				space_set_object(game->spaces[i],object_get_by_id(game,player->object) );
				
				//assigning the object to the player
				player_set_object(game->player, NO_ID);
			}
			return;
		}
	}

}


void game_callback_left(Game* game, Id id) {
	int i = 0;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	//player location is assigned to a variable "space_id"
	space_id = game_get_player_location(game);
	//If the "space_id" still equals to "NO_ID", exit
	if (NO_ID == space_id)
	{
		return;
	}
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		current_id = space_get_id(game->spaces[i]);
		//Comparing whether the field is the one on which the player is standing
		if(current_id == space_id)
		{
			current_id = space_get_west(game->spaces[i]);
			if (current_id != NO_ID)
			{
				game_callback_graps(game, id);
				game_set_player_location(game, current_id);
				game_callback_drop(game);
			}
			return;
		}
	}

}
void game_callback_right(Game* game, Id id) {
	int i = 0;
	Id current_id = NO_ID;
	Id space_id = NO_ID;
	//player location is assigned to a variable "space_id"
	space_id = game_get_player_location(game);
	//If the "space_id" still equals to "NO_ID", exit
	if (NO_ID == space_id)
	{
		return;
	}
	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
	{
		current_id = space_get_id(game->spaces[i]);
		//Comparing whether the field is the one on which the player is standing
		if (current_id == space_id)
		{
			current_id = space_get_east(game->spaces[i]);
			if (current_id != NO_ID)
			{
				game_callback_graps(game, id);
				game_set_player_location(game, current_id);
				game_callback_drop(game);
			}
			return;
		}
	}

}

void game_callback_roll_the_dice(Game* game){
  //Rolling the dice
  dice_roll(game->dice);

  return;

}
