/**
 * @brief It implements the command interpreter
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

 /*Enumeration of the main commands that the player inputs while playing*/

typedef enum enum_Command {
	NO_CMD = -1,
	UNKNOWN,
	EXIT,
	FOLLOWING,
	PREVIOUS,
	GRAPS,
	DROP,
	LEFT,
	RIGHT,
	ROLL_THE_DICE
} T_Command;

/*Declaration of the public function of the command interpreter module*/

T_Command get_user_input();

#endif
