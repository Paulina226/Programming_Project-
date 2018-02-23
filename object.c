/**
 * @brief It implements all the object related functions
 *
 * @file object.c
 * @author Adrian Callejo
 * @version 1.0
 * @date 12-02-2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"

 /*Object structure containing an Id number and a name*/
struct _Object {
	Id id;
	char name[WORD_SIZE + 1];
};

/*Object creation and destruction functions*/
Object* object_create(Id id) 
{
	Object *newObject = NULL;


	newObject = (Object *)malloc(sizeof(Object));

	if (newObject == NULL) 
	{
		return NULL;
	}

	newObject->id = id;

	newObject->name[0] = '\0';

	return newObject;
}

STATUS object_destroy(Object* object)
{
	if (!object)
	{
		return ERROR;
	}

	free(object);
	object = NULL;

	return OK;
}

/*Set functions for Id and Name*/
STATUS object_set_name(Object* object, char* name)
{
	if (!object || !name) {
		return ERROR;
	}

	if (!strcpy(object->name, name))
	{
		return ERROR;
	}

	return OK;
}

STATUS object_set_id(Object* object, Id id) 
{
	if (!object || !id) 
	{
		return ERROR;
	}

	object->id = id;

	return OK;
}

/*Get functions for Id and Name*/
Id object_get_id(Object* object) 
{
	if (!object) 
	{
		return NO_ID;
	}
	return object->id;
}

const char * object_get_name(Object* object) 
{
	if (!object)
	{
		return NULL;
	}
	return object->name;
}

/*Printing the object structure fields for debugging purposes (function not used in the main program)*/

STATUS object_print(Object* object) 
{
	if (!object)
	{
		return ERROR;
	}

	fprintf(stdout, "---> Object Id %ld\n", object->id);

	fprintf(stdout, "---> Object name %s\n", object->name);

	return OK;
}
