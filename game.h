/**
 * @brief It defines the game interface
 * for each command
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"

#define max_o 4
 /*Strcture containing player and object locations, a variable number of space containing structures and an input command*/
typedef struct _Game {
	Player* player;
	Object* object[max_o];
	Space* spaces[MAX_SPACES + 1];
	Dice* d;
	T_Command last_cmd;
} Game;

/*Declaration of the public functions of the game interface module*/
STATUS game_create(Game* game);

STATUS game_create_from_file(Game* game, char* filename);

STATUS game_update(Game* game, T_Command cmd);

Object* object_get_by_id(Game* game, Id id);

STATUS game_destroy(Game* game);

BOOL   game_is_over(Game* game);

void   game_print_screen(Game* game);

void   game_print_data(Game* game);

Id     game_get_player_location(Game* game);

Id     game_get_object_location(Game* game);

Space* game_get_space(Game* g, int s_num);

T_Command game_get_last_command(Game* game);

#endif
