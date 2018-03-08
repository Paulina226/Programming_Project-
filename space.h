/**
 * @brief It defines a space
 *
 * @file space.h
 * @author Paulina KAsperkiewicz
 * @version 3.0
 * @date 08-03-2018
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "set.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1
#define max_r 3
#define max_c 7

Space* space_create(Id id);
STATUS space_destroy(Space* space);

Id space_get_id(Space* space);
STATUS space_set_name(Space* space, char* name);
const char* space_get_name(Space* space);
STATUS space_set_gdesc(Space* space,int line, char* gdesc);
STATUS space_set_north(Space* space, Id id);
Id space_get_north(Space* space);
STATUS space_set_south(Space* space, Id id);
char *  space_get_gdesc(Space* space, int line);
Id space_get_south(Space* space);
STATUS space_set_east(Space* space, Id id);
Id space_get_east(Space* space);
STATUS space_set_west(Space* space, Id id);
Id space_get_west(Space* space);
STATUS space_set_object(Space* space, Object* object);
Set* space_get_set(Space* space);
STATUS space_add_object(Space* space, Object* object);
STATUS space_remove_object(Space* space, Object* object);
STATUS space_print(Space* space);

#endif
