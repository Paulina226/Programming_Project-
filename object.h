/**
 * @brief It defines all the object related functions
 *
 * @file object.h
 * @author Adrian Callejo
 * @version 1.0
 * @date 12-02-2018
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

Object* object_create(Id id);
STATUS object_destroy(Object* object);

STATUS object_set_name(Object* object, char* name);
STATUS object_set_id(Object* object, Id id);
Id object_get_id(Object* object);
const char * object_get_name(Object* object);

STATUS object_print(Object* object);

#endif
