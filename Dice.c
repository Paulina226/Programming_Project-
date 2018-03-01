#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

#define MAX_VALUE 6

struct _Dice{
	
	Id id;
	int val;	

};

STATUS dice_create(Dice* dice)
{
	
	dice = (Dice*)malloc(sizeof(Dice));

	dice->id = NO_ID;

	dice->val = -1;

	return OK;
}

void dice_destroy(Dice* dice){

	free(dice);

	return;
}

int dice_roll(Dice* dice){

	int val;

	srand(time(NULL));


	dice->val = ((rand()% MAX_VALUE) +1);

	val = dice->val;

	return val;	

}


void dice_print(Dice* dice){


	fprintf(stdout,"-->Id:%ld",dice->id);

	fprintf(stdout,"-->Value:%i",dice->val);

	return;
}





















