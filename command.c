/**
* @brief It implements the command interpreter
*
* @file command.c
* @author Profesores PPROG
* @version 1.0
* @date 19-12-2014
* @copyright GNU Public License
*/

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 40
#define N_CMD 7

/*Codifies player inputs if they are a string*/
char *cmd_to_str[N_CMD] = { "No command", "Unknown", "Exit", "Following", "Previous", "Pick up" , "Put in place" };

/*Codifies player inputs if they are a single character*/
char *short_cmd_to_str[N_CMD] = { "","","e","f","p","u","i" };

/*Functions used to read the user inputs and codify them for later use*/
T_Command get_user_input()
{
	T_Command cmd = NO_CMD;
	char input[CMD_LENGHT] = ""; int i = UNKNOWN - NO_CMD + 1;

	if (scanf("%s", input) > 0)
	{
		cmd = UNKNOWN;

		while (cmd == UNKNOWN && i < N_CMD)
		{
			if (!strcasecmp(input, short_cmd_to_str[i]) || !strcasecmp(input, cmd_to_str[i]))
			{
				cmd = i + NO_CMD;
			}

			else
			{
				i++;
			}
		}
	}

	return cmd;
}
