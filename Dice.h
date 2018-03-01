#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

typedef struct _Dice Dice;


/*Dice initialization function*/
STATUS dice_create(Dice* dice);

/*Dice destruction function*/
void dice_destroy(Dice* dice);

/*Dice rolling function*/
int dice_roll(Dice* dice);

/*Dice testing functions (It will print the dice number and Id for debugging purposes)*/
void dice_print(Dice* dice);


