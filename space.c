#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"
#include "object.h"

struct Space {
	Id id;
	char name[WORD_SIZE + 1];
	Id north;
	Id south;
	Id east;
	Id west;
	Set* object;
	char gdesc[max_r][max_c];
};
/* request a block of memory for struct "space" with choosen id*/
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
	newSpace->object = set_create();
	int i, j;
	for (i = 0; i < max_r; i++)
	{
		for (j = 0; i < max_c; i++) {
			newSpace->gdesc[i][j] = '\0';
		}
		
	}
	return newSpace;
}
/*destroying the space - deallocate memory block */
STATUS space_destroy(Space* space)
{
	if (!space) {
		return ERROR;
	}
	//zmiana
	set_destroy(space->object);
	// zmiana
	int i ;
	for (i = 0; i<max_r; i++)
	{
		free(space->gdesc[i]);
	}
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

/*Setting the name of space*/
STATUS space_set_gdesc(Space* space,int line, char* gdesc)
{
	if (!space || !gdesc)
	{
		return ERROR;
	}
	if (!strcpy(space->gdesc[line], gdesc))
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



/*Getting the space name */
const char * space_get_name(Space* space)
{
	if (!space)
	{
		return NULL;
	}
	return space->name;
}

char *  space_get_gdesc(Space* space, int line)
{
	if (!space)
	{
		return NULL;
	}
	return space->gdesc[line];
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


/*Adding a new object into space */
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
	add_value(space->object, object_get_id(object));
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
	char* test[max_r] = { {0} };
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
	int i;
	for (i = 0; i < max_r; i++)
	{
		test[i] = space_get_gdesc(space, i);
		fprintf(stdout, "---> %s.\n", test[i]);
	}
	
	return OK;
}
