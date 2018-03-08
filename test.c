#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "dice.h"

int main(){

Dice* d = NULL;

d = dice_create();

dice_roll(d);

dice_print(d);

dice_destroy(d);

printf("Correct\n");

  return 0;
}
