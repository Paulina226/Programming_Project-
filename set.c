#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "set.h"

struct _Set {
	Id ids[max];
	int card;
};
/* request a block of memory for struct "Set" with choosen id*/
Set* set_create() {
	Set *newSet = NULL;
	int i;

	newSet = (Set *)malloc(sizeof(Set));

	if (newSet == NULL)
	{
		return NULL;
	}
	for (i = 0; i < max; i++)
	{
		newSet->ids[i] = NO_ID;
	}
	newSet->card = 0;
	return newSet;
}
STATUS set_destroy(Set* set)
{
	if (!set) {
		return ERROR;
	}

	free(set);
	set = NULL;

	return OK;
}

STATUS set_card(Set* set, int card)
{
	if (!set || card == -1)
	{
		return ERROR;
	}
	set->card = card;
	return OK;
}
STATUS set_Ids(Set* set, Id* ids)
{
	if (!set || !ids)
	{
		return ERROR;
	}
	int i;
	for (i = 0; i < max; i++) {
		set->ids[i] = ids[i];
	}
	return OK;
}

STATUS add_value(Set* set, Id id) {
	int index = set->card;
	set->ids[index] = id;
	int len = set->card;
	set_card(set, len + 1);
	return OK;
}
STATUS remove_value(Set* set, Id id) {
	Id current_id = NO_ID;
	int counter = set->card;
	Id tmpWord[10];
	int k;
	for (k = 0; k < max; k++)
	{
		tmpWord[k] = NO_ID;
	}
	int i, j;
	j = 0;
	for (i = 0; i < max && set->ids[i] != NO_ID; i++) {
		current_id = set->ids[i];
		if (current_id == id)
		{
			tmpWord[j] = set->ids[i + 1];
			i++;
		}
		else
		{
			tmpWord[j] = set->ids[i];
		}

		j++;
	}
	set_card(set, counter - 1);
	set_Ids(set, tmpWord);
	return OK;
}
Id  set_get_ids(Set* set, Id id)
{
	if (!set)
	{
		return NULL;
	}

	return  set->ids[id];
}
int set_get_number(Set* set)
{
	if (!set)
	{
		return ERROR;
	}
	return set->card;
}

STATUS set_print(Set* set)
{
	Id idaux;
	//&idaux= NO_ID;
	//If player doesn't exist then return error
	if (!set)
		return ERROR;
	int i;
	idaux = set_get_ids(set, 0);
	// Assign value of id player to the variable idaux
	for (i = 0; i < set->ids[max] && set->ids[i] != -1; i++)
	{
		fprintf(stdout, "---> Id:  %ld.\n", idaux);
		idaux = set_get_ids(set, i + 1);
	}

	return OK;
}