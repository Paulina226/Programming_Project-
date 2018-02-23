#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"

struct _Graphic_engine
{
	Area *map, *descript, *banner, *help, *feedback;
};

/* Graphic engine initialization*/
Graphic_engine *graphic_engine_create()
{
	static Graphic_engine *ge = NULL;

	if (ge)
		return ge;
	/* Init screen and allocate memory for Graphic_engine*/
	screen_init();
	ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
	/* Set values of Graphic_engine (structure definition above)*/
	ge->map = screen_area_init(1, 1, 48, 13);
	ge->descript = screen_area_init(50, 1, 29, 13);
	ge->banner = screen_area_init(28, 15, 23, 1);
	ge->help = screen_area_init(1, 16, 78, 2);
	ge->feedback = screen_area_init(1, 19, 78, 3);

	return ge;
}
/*Graphic engine disposal*/
void graphic_engine_destroy(Graphic_engine *ge)
{
	/* Check does Graphic_engine instance exist*/
	if (!ge)
		return;
	/* Remove all elements from Graphic_engine (to destroy Graphic_engine instance)*/
	screen_area_destroy(ge->map);
	screen_area_destroy(ge->descript);
	screen_area_destroy(ge->banner);
	screen_area_destroy(ge->help);
	screen_area_destroy(ge->feedback);

	/* Destroy Graphic_engine and release the memory*/
	screen_destroy();
	free(ge);
}
/*Run graphics engine*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
	Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, ply_loc=NO_ID;
	Space* space_act = NULL;
	char obj = '\0';
	char str[255];
	T_Command last_cmd = UNKNOWN;
	extern char *cmd_to_str[];

	/* Paint the in the map area */
	/*Clear the map area of Graphic_engine*/
	screen_area_clear(ge->map);
	/* Check does id_act is not set*/
	if ((id_act = game_get_player_location(game)) != NO_ID)
	{
		space_act = game_get_space(game, id_act);
		id_back = space_get_north(space_act);
		id_next = space_get_south(space_act);
		/* Check does object location is move back*/
		if (game_get_object_location(game) == id_back)
			obj = '*';
		else
			obj = ' ';

		/* When object location is move back (id_back is not empty)*/
		if (id_back != NO_ID)
		{
			sprintf(str, "  |         %2d|", (int)id_back);
			screen_area_puts(ge->map, str);
			sprintf(str, "  |     %c     |", obj);
			screen_area_puts(ge->map, str);
			sprintf(str, "  +-----------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "        ^");
			screen_area_puts(ge->map, str);
		}
		/* Check does object location is move act*/
		if (game_get_object_location(game) == id_act)
			obj = '*';
		else
			obj = ' ';
		/* When location is move act (id_act is not empty)*/
		if (id_act != NO_ID)
		{
			sprintf(str, "  +-----------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "  | 8D      %2d|", (int)id_act);
			screen_area_puts(ge->map, str);
			sprintf(str, "  |     %c     |", obj);
			screen_area_puts(ge->map, str);
			sprintf(str, "  +-----------+");
			screen_area_puts(ge->map, str);
		}
		/* Check does object location is move next*/
		if (game_get_object_location(game) == id_next)
			obj = '*';
		else
			obj = ' ';
		/* When location is move next (id_next is not empty)*/
		if (id_next != NO_ID)
		{
			sprintf(str, "        v");
			screen_area_puts(ge->map, str);
			sprintf(str, "  +-----------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "  |         %2d|", (int)id_next);
			screen_area_puts(ge->map, str);
			sprintf(str, "  |     %c     |", obj);
			screen_area_puts(ge->map, str);
		}
	}

	/* Paint the in the description area */
	screen_area_clear(ge->descript);
	if ((obj_loc = game_get_object_location(game)) != NO_ID)
	{
		sprintf(str, "  Object location:%d", (int)obj_loc);
		screen_area_puts(ge->descript, str);
	}
	if ((ply_loc= game_get_player_location(game)) != NO_ID)
	{
		sprintf(str, "  Player location:%d", (int)ply_loc);
		screen_area_puts(ge->descript, str);
	}

	/* Paint the in the banner area */
	screen_area_puts(ge->banner, " The game of the Goose ");

	/* Paint the in the help area */
	screen_area_clear(ge->help);
	sprintf(str, " The commands you can use are:");
	screen_area_puts(ge->help, str);
	sprintf(str, "     following or f, previous or p, or exit or e, pick up or cos, put in place or cos tam");
	screen_area_puts(ge->help, str);

	/* Paint the in the feedback area */
	last_cmd = game_get_last_command(game);
	sprintf(str, " %s", cmd_to_str[last_cmd - NO_CMD]);
	screen_area_puts(ge->feedback, str);

	/* Dump to the terminal */
	screen_paint();
	printf("prompt:> ");
}
