/**
* @brief It defines a space
*
* @file space.h
* @author Profesores PPROG
* @version 1.0
* @date 13-01-2015
* @copyright GNU Public License
*/

#ifndef SET_H
#define SET_H
#include "types.h"

typedef struct _Set Set;

#define max 4

Set* set_create();
STATUS set_card(Set* set, int card);
STATUS set_Ids(Set* set, Id* ids);
STATUS add_value(Set* set, Id id);
STATUS remove_value(Set* set, Id id);
Id  set_get_ids(Set* set, Id id);
int set_get_number(Set* set);
STATUS set_print(Set* set);

#endif
