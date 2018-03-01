#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"
#include "object.h"

struct _Space {
	Id id;
	char name[WORD_SIZE + 1];
	Id north;
	Id south;
	Id east;
	Id west;
	Set* object;
};
/* request a block of memory for struct "space" with choosen id*/
Space* space_create(Id id)
{
	Space *newSpace = NULL;

	if (id == NO_ID)
		return NULL;

	newSpace = (Space *)malloc(sizeof(Space));

	if (newSpace == NULL)
	{
		return NULL;
	}
	newSpace->id = id;

	newSpace->name[0] = '\0';

	newSpace->north = NO_ID;
	newSpace->south = NO_ID;
	newSpace->east = NO_ID;
	newSpace->west = NO_ID;
	//zmiana
	newSpace->object = set_create();


	return newSpace;
}
/*destroying the space - deallocate memory block */
STATUS space_destroy(Space* space)
{
	if (!space) {
		return ERROR;
	}
	set_destroy(space->object);

	free(space);
	space = NULL;

	return OK;
}
/*Setting the name of space*/
STATUS space_set_name(Space* space, char* name)
{
	if (!space || !name)
	{
		return ERROR;
	}

	if (!strcpy(space->name, name))
	{
		return ERROR;
	}

	return OK;
}
/*Setting the north index of connection in the space */
STATUS space_set_north(Space* space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->north = id;
	return OK;
}
/*Setting the south index of connection in the space */
STATUS space_set_south(Space* space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->south = id;
	return OK;
}
/*Setting the east index of connection in the space*/
STATUS space_set_east(Space* space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->east = id;
	return OK;
}
/*Setting the west index of connection in the space */
STATUS space_set_west(Space* space, Id id)
{
	if (!space || id == NO_ID)
	{
		return ERROR;
	}
	space->west = id;
	return OK;
}
/*Setting the object into the space*/


STATUS space_set_object(Space* space, Object* object)
{
	if (!space || !object)
	{
		return ERROR;
	}

	
	if (space->object != NULL)
	{
		return ERROR;
	}
	add_value(space->object, object->id)
	return OK;
}
/*Getting the space name */
const char * space_get_name(Space* space)
{
	if (!space)
	{
		return NULL;
	}
	return space->name;
}
/*Getting item of space */
Id space_get_id(Space* space)
{
	if (!space)
	{
		return NO_ID;
	}
	return space->id;
}
/*Getting the index of linked for the north*/
Id space_get_north(Space* space)
{
	if (!space)
	{
		return NO_ID;
	}
	return space->north;
}
/*Getting the index of linked for the south*/
Id space_get_south(Space* space)
{
	if (!space)
	{
		return NO_ID;
	}
	return space->south;
}
/*Getting the index of linked for the east*/
Id space_get_east(Space* space)
{
	if (!space)
	{
		return NO_ID;
	}
	return space->east;
}
/*Getting the index of linked for the west*/
Id space_get_west(Space* space)
{
	if (!space)
	{
		return NO_ID;
	}
	return space->west;
}

/*Getting of object position*/
Set* space_get_set(Space* space)
{
	if (!space)
	{
		return NULL;
	}
	return space->object;
}

STATUS space_add_object(Space* space, Object* object) {

	add_value(space->object, object->id);
	return OK;
}

STATUS space_remove_object(Space* space, Object* object) {

	remove_value(space->object, object->id);
	return OK;
}
/*Showing linked between directions. If there is a connection, it will display the index of the item. In another case,
it will display a message of no link.*/
STATUS space_print(Space* space)
{
	Id idaux = NO_ID;

	if (!space)
	{
		return ERROR;
	}

	fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

	idaux = space_get_north(space);
	if (NO_ID != idaux)
	{
		fprintf(stdout, "---> North link: %ld.\n", idaux);
	}
	else
	{
		fprintf(stdout, "---> No north link.\n");
	}

	idaux = space_get_south(space);
	if (NO_ID != idaux)
	{
		fprintf(stdout, "---> South link: %ld.\n", idaux);
	}
	else
	{
		fprintf(stdout, "---> No south link.\n");
	}

	idaux = space_get_east(space);
	if (NO_ID != idaux)
	{
		fprintf(stdout, "---> East link: %ld.\n", idaux);
	}
	else
	{
		fprintf(stdout, "---> No east link.\n");
	}

	idaux = space_get_west(space);
	if (NO_ID != idaux)
	{
		fprintf(stdout, "---> West link: %ld.\n", idaux);
	}
	else
	{
		fprintf(stdout, "---> No west link.\n");
	}

	if (space_get_set(space))
	{
		set_print(space->object);
	}

	return OK;
}
