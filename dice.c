#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "dice.h"


struct _Dice{

	Id id;
	int val;

};

Dice* dice_create()
{

	Dice *dice;

	dice = (Dice*) malloc(sizeof(Dice));

	dice->id = NO_ID;

	dice->val = -1;

	return dice;
}

STATUS dice_set_val(Dice* dice, int value){

	dice->val = value;

	return OK;
}

STATUS dice_set_id(Dice* dice, Id id){

	dice->id = id;

	return OK;
}

void dice_destroy(Dice* dice){

	free(dice);

	return;
}

STATUS dice_roll(Dice* dice){

	if(!dice){

		return ERROR;

	}
	srand(time(NULL));

	dice_set_val(dice,((rand()% MAX_VALUE) +1));

	return OK;

}

void dice_print(Dice* dice){

	fprintf(stdout,"-->Id:%ld\n",dice->id);

	fprintf(stdout,"-->Value:%i\n",dice->val);

	return;
}
