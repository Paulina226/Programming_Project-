/**
* @brief Contains all player related function declarations
*
* @file player.h
* @author Paulina Kasperkiewicz
* @version 1.0
* @date 13-02-2018
* @copyright GNU Public License
*/

#ifndef GAMEREADER_H
#define GAMEREADER_H

#include "game.h"
#include "space.h"
#include "types.h"

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, Id Id);
Space* game_get_space(Game* game, Id id);

#endif
