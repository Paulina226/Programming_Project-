#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

typedef struct _Dice Dice;
#define MAX_VALUE 6


/*Dice initialization function*/
Dice* dice_create();

/*Dice destruction function*/
void dice_destroy(Dice* dice);

/*Dice rolling function*/
STATUS dice_roll(Dice* dice);

/*Dice testing functions (It will print the dice number and Id for debugging purposes)*/
void dice_print(Dice* dice);

/*Value setting function*/
STATUS dice_set_val(Dice* dice, int value);

/*Id setting function*/
STATUS dice_set_id(Dice* dice, Id id);
