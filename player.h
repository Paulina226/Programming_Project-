/**
* @brief Contains all player related function declarations
*
* @file player.h
* @author Paulina Kasperkiewicz
* @version 1.0
* @date 13-02-2018
* @copyright GNU Public License
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "object.h"

typedef struct _Player Player;

Player* player_create(Id id);
STATUS player_destroy(Player* player);
STATUS player_set_name(Player* player, char* name);
STATUS player_set_id(Player* player, Id id);
STATUS player_set_object(Player* player, Object* object);
STATUS player_set_location(Player* player, Id id);
Id player_get_id(Player* player);
Id player_get_location(Player* player);
const char* player_get_name(Player* player);
Object* player_get_object(Player* player);
STATUS player_print(Player* player);

#endif
